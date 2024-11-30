/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 16:11:52 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dir(t_cmd *cmd)
{
	struct stat	buf;

	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
	{
		if (stat(cmd->cmd, &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd("Minishell: Is Directory\n", STDERR_FILENO);
			exit(126);
		}
	}
}

void	check_executable(t_data **data, t_cmd *cmd, char **full_path)
{
	struct stat	buf;

	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
	{
		*full_path = ft_strdup(cmd->cmd);
		if (stat(*full_path, &buf) == -1)
		{
			free(*full_path);
			ft_putendl_fd("No such file or directory", 2);
			exit(127);
		}
		if (access(*full_path, X_OK) == -1)
		{
			free(*full_path);
			ft_putendl_fd("Permission denied", 2);
			exit(126);
		}
	}
	else
	{
		*full_path = find_path((*data)->envp, cmd->cmd);
		if (!*full_path)
			exit(ft_print_ret("Command not found\n", 127));
	}
}

void	execute_command(t_cmd *cmd, t_data **data)
{
	char	*full_path;
	char	**new_args;
	int		i;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		exit(0);
	check_executable(data, cmd, &full_path);
	check_dir(cmd);
	if (!full_path)
		exit(ft_print_ret("Command not found\n", 127));
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
	exit(127);
}

int	is_special_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	//if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	//	return (1);
	if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void	execute_pipeline(t_data **data)
{
	int idx;

	idx = 0;
	(*data)->cmdline->pipe_fd = (int **) malloc(sizeof(int *) * \
			(*data)->cmdline->count);
	while (idx < (*data)->cmdline->count - 1)
	{
		(*data)->cmdline->pipe_fd[idx] = \
			(int *) malloc(sizeof(int) * 2);
		if (pipe((*data)->cmdline->pipe_fd[idx]) == -1)
		{
			ft_putstr_fd("Broken Pipe\n", 2);
			exit(2);
		}
		idx++;
	}
	exe_pipe_while(data);
	ft_ctrl_signal();
}
