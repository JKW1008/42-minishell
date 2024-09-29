/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:03:33 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/30 00:53:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->len = 0;
}

t_token	*ft_creat_token(char *prompt, int start, int cnt)
{
	t_token	*tok;

	tok = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!tok)
		return (NULL);
	tok->value = ft_substr(prompt, start, cnt);
	tok->qt_status = ft_quote(tok->value);
	if (start > 0)
		tok->pre_sep = prompt[start - 1];
	else
		tok->pre_sep = '\0';
	tok->next = NULL;
	tok->prev = NULL;
	if (ft_valid_quotes(tok->value))
	{
		free(tok->value);
		free(tok);
		return (NULL);
	}
	return (tok);
}

void	ft_add_token_for_list(t_token *tok, t_tkn_stk **tkns)
{
	t_token	*tmp;

	if (!(*tkns)->head)
	{
		(*tkns)->head = tok;
		tok->tkn_idx = 0;
	}
	else
	{
		tmp = (*tkns)->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
		tok->prev = tmp;
	}
	(*tkns)->len++;
}

int	ft_add_token(char *prompt, int start, int cnt, t_tkn_stk **tkns)
{
	t_token	*tok;

	tok = ft_creat_token(prompt, start, cnt);
	if (!tok)
		return (1);
	ft_add_token_for_list(tok, tkns);
	return (0);
}

t_tkn_stk	*ft_tokenize(char *prompt)
{
	int			len;
	t_tkn_stk	*tokens;

	len = ft_strlen(prompt);
	ft_init_stk_tokens(&tokens);
	ft_tokenize_of_while(prompt, len, &tokens);
	return (tokens);
}
