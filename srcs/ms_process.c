/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:27:08 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:36:36 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	wait_all_children(void)
// {
// 	int		status;

// 	while (wait(&status) > 0)
// 		;
// 	if (WIFEXITED(status))
// 		ft_global_err(WEXITSTATUS(status), 1);
// 	else if (WIFSIGNALED(status))
// 		ft_global_err(128 + WTERMSIG(status), 1);
// 	else if (WIFSTOPPED(status))
// 		g_signal_received = 3;
// }

void	wait_all_children(t_cmd *cmd)
{
	int		status;

	while (cmd && waitpid(cmd->pid_, &status, 0) >= 0)
	{
		if (WIFEXITED(status) && cmd->cmdline->count == cmd->ord)
			ft_global_err(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				write(2, "^C\n", 3);
			if (WTERMSIG(status) == 3)
				write(2, "^\\Quit\n", 7);
			if (cmd->cmdline->count == cmd->ord)
				ft_global_err(128 + WTERMSIG(status), 1);
		}
		else if (WIFSTOPPED(status))
			g_signal_received = 3;
		cmd = cmd->next;
	}
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
	{
		cmd->pid_ = pid;
		command_parent(info, cmd);
	}
}
