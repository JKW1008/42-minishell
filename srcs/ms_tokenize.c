/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:03:33 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/21 21:01:59 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->len = 0;
}

int	ft_valid_quotes(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(prompt);
	if (prompt[0] == '\'' || prompt[0] == '"')
	{
		if (len < 2)
			return (1);
		if (prompt[0] == '\'' && prompt[len - 1] != '\'')
			return (1);
		if (prompt[0] == '"' && prompt[len - 1] != '"')
			return(1);
	}
	return (0);
}

int	ft_add_token(char *prompt, int cnt, t_tkn_stk **tkns)
{
	t_token	*tok;
	t_token	*tmp;

	tok = (t_token *)ft_calloc(sizeof(t_token), 1);
	tok->value = ft_substr(prompt, 0, cnt);
	tok->qt_status = ft_quote(tok->value);
	tok->next = NULL;
	if (ft_valid_quotes(tok->value))
		return (1);
	if (!(*tkns)->head)
	{
		(*tkns)->head = tok;
		tok->prev = NULL;
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
	return (0);
}

int	ft_token_metachar(char *prompt, t_tkn_stk **tkns)
{
	int	len;
	
	len = ft_strlen(prompt);
	if (len > 1 && ft_is_metachar(prompt[1]))
	{
		if (prompt[0] == prompt[1])
		{
			ft_add_token(prompt, 2, tkns);
			return (2);
		}
	}
	ft_add_token(prompt, 1, tkns);
	return (1);	
}

int	ft_token_quote(char *prompt, t_tkn_stk **tkns, char quote)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(prompt);
	while (i < len && prompt[i] != quote)
		i++;
	if (i > len)
		return (-1);
	ft_add_token(prompt, ++i, tkns);
	return (i);

}

t_tkn_stk	*ft_tokenize(char *prompt)
{
	int			i;
	int			len;
	int			cnt;
	t_tkn_stk	*tokens;

	i = 0;
	len = ft_strlen(prompt);
	ft_init_stk_tokens(&tokens);
	while (i < len)
	{
		if (ft_isspace(prompt[i]))
			i++;
		else if (ft_is_metachar(prompt[i]))
		{
			cnt = ft_token_metachar(prompt + i, &tokens);
			if (cnt == -1)
				return (ft_free_tokens(tokens));
			i += cnt;
		}
		else if (prompt[i] == '"' || prompt[i] == '\'')
		{
			cnt = ft_token_quote(prompt + i, &tokens, prompt[i]);
			if (cnt == -1)
				return (ft_free_tokens(tokens));
			i += cnt;
		}
		else
		{
			cnt = 0;
			while (i + cnt < len && !ft_is_metachar(prompt[i + cnt]) && \
					prompt[i + cnt] != '\'' && prompt[i + cnt] != '"' && \
					!ft_isspace(prompt[i + cnt]))
				cnt++;
			if (ft_add_token(prompt + i, cnt, &tokens) == -1)
				return (ft_free_tokens(tokens)); 
			i += cnt;
		}
	}
	return (tokens);
}
