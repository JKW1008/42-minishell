/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:20:47 by kjung             #+#    #+#             */
/*   Updated: 2024/11/26 22:20:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_child(t_cmd *cmd, t_pipe_info *info)
{
	if (info->prev_pipe == -1 && isatty(STDIN_FILENO))
		signal(SIGTTIN, SIG_DFL);
	else
		signal(SIGTTIN, SIG_IGN);
	default_signal();
	if (info->prev_pipe != -1)
	{
		dup2(info->prev_pipe, STDIN_FILENO);
		if (info->prev_pipe > 0)
			close(info->prev_pipe);
	}
	if (cmd->next)
		dup2(info->pipe_fd[1], STDOUT_FILENO);
	if (info->pipe_fd[0] != -1)
		close(info->pipe_fd[0]);
	if (info->pipe_fd[1] != -1)
		close(info->pipe_fd[1]);
	handle_redirections(cmd);
	if (cmd->is_builtin)
		exit(ms_execute(cmd, info->data, 1));
	else
		execute_command(cmd, info->data);
}

void	command_parent(t_pipe_info *info, t_cmd *cmd)
{
	stop_signal();
	if (info->prev_pipe != -1)
		close(info->prev_pipe);
	if (info->pipe_fd[1] != -1)
		close(info->pipe_fd[1]);
	info->prev_pipe = info->pipe_fd[0];
	if (!cmd->next)
		info->prev_pipe = -1;
}
