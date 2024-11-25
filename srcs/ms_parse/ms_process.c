/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:27:08 by kjung             #+#    #+#             */
/*   Updated: 2024/11/25 22:26:37 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		command_child(cmd, info);
	else
		command_parent(info, cmd);
}
