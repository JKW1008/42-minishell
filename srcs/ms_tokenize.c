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
	if (prompt[0] == '\'' && prompt[len] != '\'')
		return (1);
	if (prompt[0] == '"' && prompt[len] != '"')
		return(1);
	return (0);
}

int	ft_add_token(char *prompt, int cnt, t_tkn_stk **tkns)
{
	t_token	*tok;
	t_token	*tmp;

	tok = (t_token *)ft_calloc(sizeof(t_token), 1);
	tok->value = ft_substr(prompt, 0, cnt);
	if (ft_valid_quotes(tok->value))
	{
		printf("hello\n");
		return (-1);
	}

	tok->next = NULL;
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
		tok->tkn_idx = tmp->tkn_idx + 1;
	}
	(*tkns)->len++;
	printf("tok %d: %s\n", tok->tkn_idx, tok->value);
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
	if (i == len)
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
		cnt = 1;
		if (ft_isspace(prompt[i]))
			i++;
		else if (ft_is_metachar(prompt[i]))
			i += ft_token_metachar(prompt + i, &tokens);
		else if (prompt[i] == '"' || prompt[i] == '\'')
			i += ft_token_quote(prompt + i, &tokens, prompt[i]);
		else
		{
			while (!ft_isspace(prompt[i + cnt]))
				cnt++;
			if (ft_add_token(prompt + i, ++cnt, &tokens))
				ft_error("minishell : Not Valid Quotes");
			i += cnt;
		}
	}
	return (tokens);
}
