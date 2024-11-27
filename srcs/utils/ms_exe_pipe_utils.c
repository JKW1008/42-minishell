/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:41 by kjung             #+#    #+#             */
/*   Updated: 2024/11/26 22:20:36 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_pipe_while(t_data **data, t_pipe_info *info)
{
	t_cmd	*cmd;

	cmd = (*data)->cmdline->head;
	while (cmd)
	{
		if (cmd->is_builtin && is_special_builtin(cmd))
		{
			ms_execute(cmd, data, 0);
			if (!cmd->next)
				return ;
		}
		else if (cmd->rdr_cnt > 0 && (!cmd->cmd || cmd->cmd[0] == '\0'))
			handle_redirection_only(cmd, info);
		else
			process_command(cmd, info);
		cmd = cmd->next;
		// printf("%ld", ft_global_err(0, 0));
	}
	wait_all_children();
	//printf("err %ld %ld\n", ft_global_err(0, 0), ft_global_err(0, 2));
}

// void	manage_fd(t_pipe_info *info)
// {
// 	dup2(info->stdin_backup, STDIN_FILENO);
// 	dup2(info->stdout_backup, STDOUT_FILENO);
// 	close(info->stdin_backup);
// 	close(info->stdout_backup);
// }
