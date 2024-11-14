/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/12 13:08:01 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	destroy_token(t_data **data)
{
	t_token *token;
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

void	destroy_cmdline(t_data **data)
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
		while (i < cmd->rdr_cnt)
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

void	destory_heredoc(t_heredoc_list *h_list)
{
	int	i;
	
	i = 0;
	while (i < h_list->count)
	{
		free(h_list->heredocs[i].content);
		free(h_list->heredocs[i].delimiter);
		i++;
	}
	ft_memset(h_list, 0, sizeof(t_heredoc_list));
}

void	ft_destroy_parser_context(t_data **data, t_heredoc_list *h_list)
{
	if ((*data)->cmdline)
	{
		destroy_cmdline(data);
		free((*data)->cmdline);
		(*data)->cmdline = NULL;
	}
	if ((*data)->tkn)
		destroy_token(data);
	destory_heredoc(h_list);
}