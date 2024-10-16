/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:28:23 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 21:34:47 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_cmd_for_lword(t_cmd **cmd, t_token **tkn)
{
	(*cmd)->args = ft_calloc(sizeof(char *), 2);
	(*cmd)->args[0] = ft_strdup((*tkn)->value);
	(*cmd)->arg_cnt = 1;
}

t_cmd	*ft_create_cmd(t_token **tkn, t_data **data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		exit(EXIT_FAILURE);
	if ((*tkn)->token_type == l_pipe)
		(*tkn) = (*tkn)->next;
	if (ft_is_heredoc((*tkn)->value))
	{
		cmd->cmd = ft_strdup("<<");
		cmd->is_heredoc = 1;
		(*tkn) = (*tkn)->next;
		if (*tkn && (*tkn)->token_type == l_word)
			ft_create_cmd_for_lword(&cmd, tkn);
	}
	else
	{
		ft_cmd_rdr(cmd, *tkn);
		ft_alloc_simplecmd(cmd, *tkn);
	}
	cmd->prompt = ft_strdup((*data)->prompt);
	if (ft_is_builtin(cmd->cmd) == 1)
		cmd->is_builtin = 1;
	return (cmd);
}

int	ft_append_cmd(t_cmd *cmd, t_cmdline *cmdline)
{
	t_cmd	*tmp;

	if (cmdline->head)
	{
		tmp = cmdline->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	else
		cmdline->head = cmd;
	cmdline->count++;
	return (0);
}
