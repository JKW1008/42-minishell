/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:32:09 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/26 22:11:26 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_global_err(130, 1);
		write(STDOUT_FILENO, 0, 0);
	}
}

void	ft_heredoc_gnl(t_cmd *cmd, int i, int fd[2])
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, cmd->rdr[i]->file, \
				ft_strlen(cmd->rdr[i]->file)) == 0
			&& line[ft_strlen(cmd->rdr[i]->file)] == '\n')
			break ;
		if (ft_strlen(line) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd[1]);
}

static void	process_heredoc_new(t_cmd *cmd, int i)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		ft_error("Broken Pipe\n");
	pid = fork();
	if (pid < 0)
		ft_error("Fork Failed\n");
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sighandler);
		signal(SIGQUIT, SIG_IGN);
		ft_heredoc_gnl(cmd, i, fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		close(fd[1]);
		cmd->rdr[i]->fd = fd[0];
	}
	ft_ctrl_signal();
}

static void	find_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->rdr_cnt)
	{
		if (cmd->rdr[i]->type == RD_HEREDOC)
			process_heredoc_new(cmd, i);
		i++;
	}
}

void	process_heredoc(t_data **data)
{
	t_cmd	*tmp;
	int		i;

	i = 1;
	if (ft_global_err(0, 0) != 0)
		return ;
	while (i <= (*data)->cmdline->count)
	{
		tmp = (*data)->cmdline->head;
		while (tmp && tmp->prompt)
		{
			if (tmp->ord == i && tmp->is_heredoc)
				find_heredoc(tmp);
			tmp = tmp->next;
		}
		i++;
	}
}
