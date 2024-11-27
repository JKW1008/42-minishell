/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:07:18 by kjung             #+#    #+#             */
/*   Updated: 2024/11/26 22:13:56 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	hro_child_while(char *buffer, size_t buffer_size)
// {
// 	ssize_t	bytes_read;
// 	int		empty_lines;

// 	empty_lines = 0;
// 	bytes_read = read(STDIN_FILENO, buffer, buffer_size);
// 	while (bytes_read > 0)
// 	{
// 		if (bytes_read == 1 && buffer[0] == '\n')
// 		{
// 			empty_lines++;
// 			if (empty_lines >= 2)
// 				break ;
// 		}
// 		else
// 			empty_lines = 0;
// 		write(STDOUT_FILENO, buffer, bytes_read);
// 		bytes_read = read(STDIN_FILENO, buffer, buffer_size);
// 	}
// }

// void	hro_child_while(char *buffer, size_t buffer_size)
// {
// 	ssize_t	bytes_read;
// 	int		empty_lines;

// 	empty_lines = 0;
// 	bytes_read = read(STDIN_FILENO, buffer, buffer_size);
// 	// heredoc만 있고 파이프가 있는 경우는 읽기만 하고 쓰지 않음
// 	if (isatty(STDOUT_FILENO))  // 표준 출력이 터미널인 경우만 출력
// 	{
// 		while (bytes_read > 0)
// 		{
// 			if (bytes_read == 1 && buffer[0] == '\n')
// 			{
// 				empty_lines++;
// 				if (empty_lines >= 2)
// 					break ;
// 			}
// 			else
// 				empty_lines = 0;
// 			write(STDOUT_FILENO, buffer, bytes_read);
// 			bytes_read = read(STDIN_FILENO, buffer, buffer_size);
// 		}
// 	}
// }

void	hro_child(t_pipe_info *info, t_cmd *cmd)
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
	exit(0);
}

void	hro_pa(t_cmd *cmd, t_pipe_info *info, int *pid)
{
	if (info->prev_pipe != -1)
	{
		close(info->prev_pipe);
		info->prev_pipe = -1;
	}
	if (cmd->next)
	{
		if (info->pipe_fd[1] != -1)
			close(info->pipe_fd[1]);
		info->prev_pipe = info->pipe_fd[0];
	}
	waitpid(pid, NULL, 0);
}

void	hro_err(t_pipe_info *info)
{
	if (info->pipe_fd[0] != -1)
		close(info->pipe_fd[0]);
	if (info->pipe_fd[1] != -1)
		close(info->pipe_fd[1]);
	perror("fork");
	exit(1);
}

void	handle_redirection_only(t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	info->pipe_fd[0] = -1;
	info->pipe_fd[1] = -1;
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
		hro_err(info);
	if (pid == 0)
	{
		if (cmd->next && info->pipe_fd[0] != -1)
			close(info->pipe_fd[0]);
		hro_child(info, cmd);
	}
	else
		hro_pa(cmd, info, cmd);
}
