/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:07:18 by kjung             #+#    #+#             */
/*   Updated: 2024/11/29 19:45:58 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	waitpid(*pid, NULL, 0);
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
		hro_pa(cmd, info, &pid);
}
