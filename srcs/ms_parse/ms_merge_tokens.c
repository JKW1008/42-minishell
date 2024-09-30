/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_merge_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:38:37 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/23 13:38:39 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		ft_tkn_free(t_token *tkn)
{
	free(tkn->value);
	free(tkn);
}

static size_t	ft_reidx_tkns(t_tkn_stk *stack)
{
	int		idx;
	t_token *token;

	idx = 0;
	token = stack->head;
	while (token)
	{
		token->tkn_idx = idx++;
		token = token->next;
	}
	stack->len = idx;
	return (0);
}

static t_token	*merge_tokens(t_token *tkn, t_token *prev)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	new->value = ft_strjoin(prev->value, tkn->value);
	if (prev->prev)
	{
		new->prev = prev->prev;
		prev->prev->next = new;
	}
	else
		new->prev = NULL;
	if (tkn->next)
	{
		new->next = tkn->next;
		tkn->next->prev = new;
	}
	else
		new->next = NULL;
	new->token_type = l_word;
	new->pre_sep = prev->pre_sep;
	new->qt_status = mixte;
	ft_tkn_free(tkn);
	ft_tkn_free(prev);
	return (new);
}

size_t	ft_merge_tokens(t_data **data)
{
	t_token	*tkn;
	t_token *prev;

	prev = NULL;
	tkn = (*data)->tkn->head;
	while (tkn)
	{
		if (tkn->pre_sep == '\'' || tkn->pre_sep == '"')
			tkn = merge_tokens(tkn, prev);
		if (tkn->next)
		{
			prev = tkn;
			tkn = tkn->next;
		}
		else
			return (0);
	}
	ft_reidx_tkns((*data)->tkn);
	return (0);
}
	
