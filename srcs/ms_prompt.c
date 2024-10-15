/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/15 21:46:03 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

char	*set_heredoc(t_cmd *node)
{
	char	*line;
	char	*result;
	char	*new_result;
	size_t	res_len;
	size_t	res_cap;

	result = NULL;
	res_len = 0;
	res_cap = 0;
	printf("%s\n", node->args[0]);
	while (1)
	{
		line = get_input("> ");
		if (!line || (ft_strncmp(line, node->args[0], ft_strlen(node->args[0])) == 0 && ft_strlen(line) == ft_strlen(node->args[0])))
		{
			free(line);
			break;
		}
		if (res_len + ft_strlen(line) + 2 > res_cap)
		{
			if (res_cap == 0)
				res_cap = 1024;
			else
				res_cap = res_cap * 2;
			new_result = realloc(result, res_cap);
			if (!new_result)
			{
				free(result);
				free(line);
				return (NULL);
			}
			result = new_result;
		}
		ft_strlcpy(result + res_len, line, ft_strlen(line) + 1);
		res_len += ft_strlen(line);
		result[res_len++] = '\n';
		result[res_len] = '\0';
		free(line);
	}
	return (result);
}

void process_commands(t_data **data, t_heredoc_list *heredoc_list)
{
    t_cmd *tmp;
    char *here_doc;
    int pipe_fd[2];
    int stdout_backup = -1;

    tmp = (*data)->cmdline->head;
    heredoc_list->count = 0;
    while (tmp && tmp->prompt)
    {
        if (tmp->is_heredoc)
        {
            here_doc = set_heredoc(tmp);
            if (here_doc && heredoc_list->count < MAX_HEREDOCS)
            {
                heredoc_list->heredocs[heredoc_list->count].content = here_doc;
                heredoc_list->heredocs[heredoc_list->count].delimiter = ft_strdup(tmp->args[0]);
                heredoc_list->count++;
            }
            else
                free(here_doc);
        }
        else if (tmp->is_builtin && tmp->next) // 빌트인 명령어이고 파이프가 있는 경우
        {
            pipe(pipe_fd);
            stdout_backup = dup(STDOUT_FILENO);
            dup2(pipe_fd[1], STDOUT_FILENO);
            
            ms_execute(tmp, data);
            
            fflush(stdout);
            close(pipe_fd[1]);
            dup2(stdout_backup, STDOUT_FILENO);
            close(stdout_backup);
            
            // 파이프의 읽기 끝을 다음 명령어의 표준 입력으로 설정
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
        }
        tmp = tmp->next;
    }
}

void handle_redirections(t_cmd *cmd, t_heredoc_list *heredoc_list)
{
    for (int i = 0; i < cmd->rdr_cnt; i++)
    {
        int fd;
        if (cmd->rdr[i]->type == RD_IN)
        {
            fd = open(cmd->rdr[i]->file, O_RDONLY);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (cmd->rdr[i]->type == RD_OUT)
        {
            fd = open(cmd->rdr[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd->rdr[i]->type == RD_APPEND)
        {
            fd = open(cmd->rdr[i]->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd->rdr[i]->type == RD_HEREDOC)
        {
            // heredoc 처리
            for (int j = 0; j < heredoc_list->count; j++)
            {
                if (strcmp(cmd->rdr[i]->file, heredoc_list->heredocs[j].delimiter) == 0)
                {
                    int pipefd[2];
                    if (pipe(pipefd) == -1)
                    {
                        perror("pipe");
                        exit(1);
                    }
                    write(pipefd[1], heredoc_list->heredocs[j].content, strlen(heredoc_list->heredocs[j].content));
                    close(pipefd[1]);
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);
                    break;
                }
            }
        }
    }
}
void execute_pipeline(t_data **data, t_heredoc_list *heredoc_list)
{
    t_cmd *cmd;
    int pipe_fd[2];
    int prev_pipe = -1;
    pid_t pid;

    cmd = (*data)->cmdline->head;
    while (cmd)
    {
        if (cmd->next && pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)  // Child process
        {
            if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            if (cmd->next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            handle_redirections(cmd, heredoc_list);

            if (cmd->is_builtin)
            {
                ms_execute(cmd, data);
                exit(0);
            }
            else
            {
                char *full_path = find_path((*data)->envp, cmd->cmd);
                if (full_path)
                {
                    char **new_args = malloc(sizeof(char *) * (cmd->arg_cnt + 2));
                    new_args[0] = cmd->cmd;
                    for (int i = 0; i < cmd->arg_cnt; i++)
                    {
                        new_args[i + 1] = cmd->args[i];
                    }
                    new_args[cmd->arg_cnt + 1] = NULL;

                    execve(full_path, new_args, (*data)->envp);
                    free(new_args);
                    free(full_path);
                }
                fprintf(stderr, "Command not found: %s\n", cmd->cmd);
                exit(1);
            }
        }
        else  // Parent process
        {
            if (prev_pipe != -1)
                close(prev_pipe);
            
            if (cmd->next)
            {
                close(pipe_fd[1]);
                prev_pipe = pipe_fd[0];
            }
        }

        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}

void	ft_prompt(t_data **data)
{
	char	*input;
	t_heredoc_list	heredoc_list = {0};
	int		i;

	while (1)
	{
		input = readline("$ ");
		if (!input)
			break ;
		(*data)->prompt = input;
		if (ft_strlen(input))
		{
			ft_parser(data);
			process_commands(data, &heredoc_list);
			execute_pipeline(data, &heredoc_list);
			add_history(input);
		}
		free(input);
		i = 0;
		while (i < heredoc_list.count)
		{
			free(heredoc_list.heredocs[i].content);
			free(heredoc_list.heredocs[i].delimiter);
			i++;
		}
	}
	return ;
}
