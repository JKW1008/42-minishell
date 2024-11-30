/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:50:41 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 14:26:57 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_pipe_while(t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->cmdline->head;

	while (cmd)
	{
		printf("나! :%d %s\n", cmd->ord, cmd->cmd);
		/*if (!cmd->next && cmd->is_builtin && is_special_builtin(cmd))
		{
			ms_execute(cmd, data, 0);
			if (!cmd->next)
				return ;
		}
		else if (cmd->rdr_cnt > 0 && (!cmd->cmd || cmd->cmd[0] == '\0'))
			handle_redirection_only(cmd);
		else*/
			process_command(cmd);
			ft_putnbr_fd(cmd->pid, 2);
			write(2,"\n",1);
		cmd = cmd->next;
	}
	wait_all_children((*data)->cmdline->head);
}
