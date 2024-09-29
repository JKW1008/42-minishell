/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:38:00 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 02:11:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_execute(t_cmd *node, t_data **data)
{
	if (!ft_strncmp(node->cmd, "cd", 2))
		cd_cmd(data);
	else if (!ft_strncmp(node->cmd, "pwd", 4))
		print_dir();
	else if (!ft_strncmp(node->cmd, "env", 4))
		env_command(data);
	else if (!ft_strncmp(node->cmd, "exit", 4))
		do_exit((*data)->prompt);
	else if (!ft_strncmp(node->cmd, "export", 6))
		export(data);
	else if (!ft_strncmp(node->cmd, "unset ", 5))
		do_unset(data);
	else if (!ft_strncmp(node->cmd, "echo", 4))
		do_echo(data);
}
