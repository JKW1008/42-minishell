/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/11/22 18:06:29 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dir(t_cmd *cmd)
{
	struct stat	*buf;

	buf = ft_calloc(sizeof(struct stat), 1);
	stat(cmd->cmd, buf);
	if (S_ISDIR(buf->st_mode))
	{
		ft_putstr_fd("Minishell: Is Directory\n", STDERR_FILENO);
		free(buf);
		exit(1);
	}
	free(buf);
	return ;
}

void	execute_command(t_cmd *cmd, t_data **data)
{
	char	*full_path;
	char	**new_args;
	int		i;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		exit(0);
	check_dir(cmd);
	full_path = find_path((*data)->envp, cmd->cmd);
	if (!full_path)
		exit(fprintf(stderr, "Command not found: %s\n", cmd->cmd));
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

int	is_special_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_pipeline(t_data **data)
{
	t_pipe_info	info;
	pid_t		*pids;
	int			i;

	i = 0;
	pids = malloc(sizeof(pid_t) * (*data)->cmdline->count);
	if (!pids)
	{
		perror("malloc");
		exit(1);
	}
	init_info(data, &info);
	while (i <= (*data)->cmdline->count)
		exe_pipe_while(data, &info, i++);
	wait_all_children();
	manage_fd(&info);
	free(pids);
	ft_ctrl_signal();
}
