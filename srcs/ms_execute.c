/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:38:00 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 23:53:17 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_execute(t_cmd *node, t_data **data, int in_child)
{
	if (!ft_strncmp(node->cmd, "echo", 4))
		return (do_echo(node, data));
	else if (!ft_strncmp(node->cmd, "cd", 2))
	{
		if (!in_child)
			cd_cmd(node, data);
		return (0);
	}
	else if (!ft_strncmp(node->cmd, "pwd", 4))
		return (print_dir());
	else if (!ft_strncmp(node->cmd, "export", 6))
	{
		if (!in_child)
			export(node, data);
		return (0);
	}
	else if (!ft_strncmp(node->cmd, "unset", 5))
	{
		if (!in_child)
			do_unset(node, data);
		return (0);
	}
	else if (!ft_strncmp(node->cmd, "env", 4))
		return (env_command(data));
	else if (!ft_strncmp(node->cmd, "exit", 4))
	{
		if (!in_child)
			do_exit(node);
		return (0);
	}
	return (1);
}
