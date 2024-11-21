/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_destroy_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/21 17:49:21 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	destroy_token(t_data **data)
{
	t_token	*token;
	t_token	*next;

	if (!(*data)->tkn)
		return ;
	token = (*data)->tkn->head;
	while (token)
	{
		free(token->value);
		next = token->next;
		free(token);
		token = next;
	}
	free((*data)->tkn);
	(*data)->tkn = NULL;
	return ;
}

static void	destroy_cmdline(t_data **data)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		i;

	cmd = (*data)->cmdline->head;
	while (cmd)
	{
		i = 0;
		free(cmd->cmd);
		free(cmd->prompt);
		while (cmd->rdr[i])
		{
			free(cmd->rdr[i]->file);
			free(cmd->rdr[i++]);
		}
		i = 0;
		while (i < cmd->arg_cnt)
			free(cmd->args[i++]);
		free(cmd->args);
		free(cmd->rdr);
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

void	ft_destroy_parser_context(t_data **data)
{
	if ((*data)->cmdline)
	{
		destroy_cmdline(data);
		free((*data)->cmdline);
		(*data)->cmdline = NULL;
	}
	if ((*data)->tkn)
		destroy_token(data);
	free((*data)->prompt);
	(*data)->prompt = NULL;
}
