/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:27:08 by kjung             #+#    #+#             */
/*   Updated: 2024/11/25 22:27:23 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_children(t_cmd *cmd)
{
	int		status;

	while (cmd && waitpid(cmd->pid, &status, 0) >= 0)
	{
		printf("wait :%d %s\n", cmd->pid, cmd->cmd);
		if (WIFEXITED(status))
			ft_global_err(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				write(2, "^C\n", 3);
			if (WTERMSIG(status) == 3)
				write(2, "^\\Quit\n", 7);
			ft_global_err(128 + WTERMSIG(status), 1);
		}
		else if (WIFSTOPPED(status))
			g_signal_received = 3;
		cmd = cmd->next;
	}
}

void	process_command(t_cmd *cmd)
{
	pid_t	pid;

	//if (cmd->next)
	//{
	//	if (pipe(info->pipe_fd) == -1)
	//	{
	//		perror("pipe");
	//		exit(1);
	//	}
	//}
	pid = fork();
	printf("p: %d\n", pid);
	
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		command_child(cmd);
	else
	{
		cmd->pid = pid;
		command_parent(cmd);
		//if (cmd->ord != 0)
		//	close(cmd->cmdline->pipe_fd[cmd->ord - 1][0]);
		//if (cmd->ord != cmd->cmdline->count)
		//	close(cmd->cmdline->pipe_fd[cmd->ord - 1][1]);

	}
}
