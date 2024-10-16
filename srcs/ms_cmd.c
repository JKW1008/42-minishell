/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/10/17 00:49:10 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_command(t_cmd *cmd, t_data **data)
{
	char	*full_path;
	char	**new_args;
	int		i;

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
	handle_redirections(cmd, info->heredoc_list);
	if (cmd->is_builtin)
		exit(ms_execute(cmd, info->data, 1));
	else
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
		handle_child_process(cmd, info);
	else
		handle_parent_process(cmd, info);
}

void	execute_pipeline(t_data **data, t_heredoc_list *heredoc_list)
{
	t_cmd		*cmd;
	t_pipe_info	info;

	info.prev_pipe = -1;
	info.stdin_backup = dup(STDIN_FILENO);
	info.stdout_backup = dup(STDOUT_FILENO);
	info.heredoc_list = heredoc_list;
	info.data = data;
	cmd = (*data)->cmdline->head;
	while (cmd)
	{
		if (cmd->is_builtin && is_special_builtin(cmd))
			ms_execute(cmd, data, 0);
		else
			process_command(cmd, &info);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(info.stdin_backup, STDIN_FILENO);
	dup2(info.stdout_backup, STDOUT_FILENO);
	close(info.stdin_backup);
	close(info.stdout_backup);
}
