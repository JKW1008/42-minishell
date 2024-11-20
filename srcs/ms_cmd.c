/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/11/20 17:43:33 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_signal_received;

void	wait_all_children(void)
{
	int		status;

	while (wait(&status) > 0)
	 ;
	if (WIFEXITED(status))
		ft_global_err(WEXITSTATUS(status), 1);
	else if (WIFSIGNALED(status))
		ft_global_err(128 + WTERMSIG(status), 1);
    else if (WIFSTOPPED(status))
		g_signal_received = 3;
}

// void	cat_command(t_cmd *cmd)
// {
// 	if (ft_strncmp(cmd->cmd, "cat", 4) == 0 && cmd->arg_cnt == 0)
// 	{
// 		char buffer[4096];
// 		ssize_t bytes_read;
// 		int empty_lines = 0;

// 		if (isatty(STDIN_FILENO))
// 		{
// 			while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
// 			{
// 				if (bytes_read == 1 && buffer[0] == '\n')
// 				{
// 					empty_lines++;
// 					if (empty_lines >= 2)
// 						break;
// 				}
// 				else
// 					empty_lines = 0;
// 				write(STDOUT_FILENO, buffer, bytes_read);
// 			}
// 		}
// 		else
// 		{
// 			while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
// 				write(STDOUT_FILENO, buffer, bytes_read);
// 		}
// 		exit(0);
// 	}
// }

void check_dir(t_cmd *cmd)
{
	struct stat	*buf;

	buf = ft_calloc(sizeof(struct stat), 1);
	stat(cmd->cmd, buf);
	if (S_ISDIR(buf->st_mode))
	{
		ft_putstr_fd("Minishell: Is Directory\n", STDERR_FILENO);
		free(buf);
		exit(1);
	}
	free(buf);
	return ;
}

void execute_command(t_cmd *cmd, t_data **data)
{
	char	*full_path;
	char	**new_args;
	int		i;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		exit(0);
	// cat_command(cmd);
	check_dir(cmd);
	full_path = find_path((*data)->envp, cmd->cmd);
	if (!full_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd);
		exit(1);
	}
	new_args = malloc(sizeof(char *) * (cmd->arg_cnt + 2));
	if (!new_args)
	{
		perror("malloc");
		exit(1);
	}
	new_args[0] = cmd->cmd;
	i = -1;
	while (++i < cmd->arg_cnt)
		new_args[i + 1] = cmd->args[i];
	new_args[cmd->arg_cnt + 1] = NULL;
	execve(full_path, new_args, (*data)->envp);
	perror("execve");
	exit(1);
}

void	handle_child_process(t_cmd *cmd, t_pipe_info *info)
{
	if (cmd->next)
	{
		close(info->pipe_fd[0]);
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		close(info->pipe_fd[1]);
	}
	if (info->prev_pipe != -1)
	{
		dup2(info->prev_pipe, STDIN_FILENO);
		close(info->prev_pipe);
	}
	handle_redirections(cmd);
	if (cmd->is_builtin)
		exit(ms_execute(cmd, info->data, 1));
	else if (!cmd->is_builtin && !cmd->is_heredoc)
		execute_command(cmd, info->data);
}

void	handle_parent_process(t_cmd *cmd, t_pipe_info *info)
{
	if (info->prev_pipe != -1)
		close(info->prev_pipe);
	if (cmd->next)
	{
		close(info->pipe_fd[1]);
		info->prev_pipe = info->pipe_fd[0];
	}
	else
		info->prev_pipe = -1;
}

int	is_special_builtin(t_cmd *cmd)
{
	if (!cmd->next)
		return (1);
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	handle_redirection_only(t_cmd *cmd, t_pipe_info *info)
{
	pid_t pid;
	char buffer[4096];
	ssize_t bytes_read;
	int empty_lines;
	
	pid = fork();
	empty_lines = 0;
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (info->prev_pipe != -1)
		{
			dup2(info->prev_pipe, STDIN_FILENO);
			close(info->prev_pipe);
		}
		if (cmd->next && info->pipe_fd[1] != -1)
		{
			dup2(info->pipe_fd[1], STDOUT_FILENO);
			close(info->pipe_fd[1]);
		}
		handle_redirections(cmd);
		while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
		{
			if (bytes_read == 1 && buffer[0] == '\n')
			{
				empty_lines++;
				if (empty_lines >= 2)
					break;
			}
			else
				empty_lines = 0;
			write(STDOUT_FILENO, buffer, bytes_read);
		}
		exit(0);
	}
	else
	{
		if (info->prev_pipe != -1)
			close(info->prev_pipe);
		if (cmd->next)
		{
			close(info->pipe_fd[1]);
			info->prev_pipe = info->pipe_fd[0];
		}
		else
			info->prev_pipe = -1;
	}
}

void	default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	return ;
}

void	stop_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return ;
}

void	process_command(t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(info->pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		handle_redirections(cmd);
		default_signal();
		if (info->prev_pipe != -1)
		{
			dup2(info->prev_pipe, STDIN_FILENO);
			close(info->prev_pipe);
		}
		if (cmd->next)
			dup2(info->pipe_fd[1], STDOUT_FILENO);
		close(info->pipe_fd[0]);
		close(info->pipe_fd[1]);
		if (cmd->is_builtin)
			exit(ms_execute(cmd, info->data, 1));
		else
			execute_command(cmd, info->data);
	}
	else
	{
		stop_signal();
		if (info->prev_pipe != -1)
			close(info->prev_pipe);
		close(info->pipe_fd[1]);
		info->prev_pipe = info->pipe_fd[0];
		if (!cmd->next)
			info->prev_pipe = -1;
	}
}

void execute_pipeline(t_data **data)
{
	t_cmd		*cmd;
	t_pipe_info	info;
	pid_t		*pids;
	int			cmd_count;

	cmd = (*data)->cmdline->head;
	cmd_count = 0;
	while (cmd)
	{
		cmd_count++;
		cmd = cmd->next;
	}
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		perror("malloc");
		exit(1);
	}
	info.prev_pipe = -1;
	info.stdin_backup = dup(STDIN_FILENO);
	info.stdout_backup = dup(STDOUT_FILENO);
	info.data = data;
	cmd = (*data)->cmdline->head;
	while (cmd)
	{
		if (cmd->is_builtin && is_special_builtin(cmd))
			ms_execute(cmd, data, 0);
		else if (cmd->rdr_cnt > 0 && (!cmd->cmd || cmd->cmd[0] == '\0'))
			handle_redirection_only(cmd, &info);
		else
			process_command(cmd, &info);
		cmd = cmd->next;
	}
	wait_all_children();
	dup2(info.stdin_backup, STDIN_FILENO);
	dup2(info.stdout_backup, STDOUT_FILENO);
	close(info.stdin_backup);
	close(info.stdout_backup);
	free(pids);
	ft_ctrl_signal();
}
