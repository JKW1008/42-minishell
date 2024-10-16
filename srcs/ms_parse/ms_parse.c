/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 21:35:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init_cmdline(t_data **data)
{
	t_cmdline	*cmdline;

	cmdline = (t_cmdline *) malloc(sizeof(t_cmdline));
	if (!cmdline)
		return (1);
	cmdline->count = 0;
	cmdline->head = NULL;
	(*data)->cmdline = cmdline;
	return (0);
}

static size_t	ft_check_tknlen(t_token *tkn)
{
	t_token	*tmp;
	size_t	token_count;

	tmp = tkn;
	token_count = 0;
	if (tmp->token_type == l_pipe && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->token_type != l_pipe)
	{
		tmp = tmp->next;
		token_count++;
	}
	return (token_count);
}

static size_t	parse(t_data **data)
{
	t_token	*token;

	(*data)->cmdline = ft_calloc(sizeof(t_cmdline), 1);
	token = (*data)->tkn->head;
	while (token->tkn_idx < (*data)->tkn->len)
	{
		if (token->tkn_idx == 0 || token->token_type == l_pipe)
		{
			if (ft_check_tknlen(token) == 0)
				return (2);
			ft_append_cmd(ft_create_cmd(&token, data), \
				(*data)->cmdline);
		}
		if (token->next)
			token = token->next;
		else
			return (0);
	}
	return (0);
}

size_t	ft_parser(t_data **data)
{
	(*data)->errno_ = 0;
	(*data)->errno_ = ft_lexer(data);
	(*data)->errno_ = ft_merge_tokens(data);
	(*data)->errno_ = parse(data);
	(*data)->errno_ = ft_sort_ord(data);
	if ((*data)->errno_)
		printf("minishell: syntax error\n");
	return (ft_strlen((*data)->prompt));
}
