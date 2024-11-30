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

void	hro_child(t_cmd *cmd)
{
	//if (info->prev_pipe != -1)
	//{
	//	dup2(info->prev_pipe, STDIN_FILENO);
	//	close(info->prev_pipe);
	//}
	//if (cmd->next && info->pipe_fd[1] != -1)
	//{
	//	dup2(info->pipe_fd[1], STDOUT_FILENO);
	//	close(info->pipe_fd[1]);
	//}
	if (cmd->ord != 1)
	{
		close(cmd->cmdline->pipe_fd[cmd->ord - 2][1]);
		dup2(cmd->cmdline->pipe_fd[cmd->ord - 2][0], STDIN_FILENO);
		close(cmd->cmdline->pipe_fd[cmd->ord - 2][0]);
		
	}
	if (cmd->ord != cmd->cmdline->count)
	{
		close(cmd->cmdline->pipe_fd[cmd->ord - 1][0]);
		dup2(cmd->cmdline->pipe_fd[cmd->ord - 1][1], STDOUT_FILENO);
		close(cmd->cmdline->pipe_fd[cmd->ord - 1][1]);
		
	}
	handle_redirections(cmd);
	exit(0);
}

void	hro_pa(t_cmd *cmd)
{
	//if (info->prev_pipe != -1)
	//{
	//	close(info->prev_pipe);
	//	info->prev_pipe = -1;
	//}
	//if (cmd->next)
	//{
	//	if (info->pipe_fd[1] != -1)
	//		close(info->pipe_fd[1]);
	//	info->prev_pipe = info->pipe_fd[0];
	//}
	//waitpid(*pid, NULL, 0);
	if (cmd->ord != 1)
	{
		close(cmd->cmdline->pipe_fd[cmd->ord - 2][1]);
	}
	if (cmd->ord != cmd->cmdline->count)
	{
		close(cmd->cmdline->pipe_fd[cmd->ord - 1][0]);
	}
}

void	hro_err(t_cmd *cmd)
{
	//if (info->pipe_fd[0] != -1)
	//	close(info->pipe_fd[0]);
	//if (info->pipe_fd[1] != -1)
	//	close(info->pipe_fd[1]);
	if (cmd->ord != 1)
		close(cmd->cmdline->pipe_fd[cmd->ord - 2][0]);
	if (cmd->ord != cmd->cmdline->count)
		close(cmd->cmdline->pipe_fd[cmd->ord - 1][1]);
	perror("fork");
	exit(1);
}

void	handle_redirection_only(t_cmd *cmd)
{
	pid_t	pid;

	//info->pipe_fd[0] = -1;
	//info->pipe_fd[1] = -1;
	//if (cmd->next)
	//{
	//	if (pipe(info->pipe_fd) == -1)
	//	{
	//		perror("pipe");
	//		exit(1);
	//	}
	//}
	pid = fork();

	if (pid == -1)
		hro_err(cmd);
	if (pid == 0)
	{
		//if (cmd->next && info->pipe_fd[0] != -1)
		//	close(info->pipe_fd[0]);
		//if (cmd->ord != 1)
		//	close(cmd->cmdline->pipe_fd[cmd->ord - 2][0]);
		hro_child(cmd);
	}
	else
	{
		cmd->pid = pid;
		hro_pa(cmd);
	}
		
		
}
