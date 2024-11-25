/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:20:47 by kjung             #+#    #+#             */
/*   Updated: 2024/11/25 22:21:32 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_child(t_cmd *cmd, t_pipe_info *info)
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

void	command_parent(t_pipe_info *info, t_cmd *cmd)
{
	stop_signal();
	if (info->prev_pipe != -1)
		close(info->prev_pipe);
	close(info->pipe_fd[1]);
	info->prev_pipe = info->pipe_fd[0];
	if (!cmd->next)
		info->prev_pipe = -1;
	wait_all_children();
}
