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

//t_token	*creat_token(int idx, t_lex_tbl type, t_quote_tbl qt_status, char *value)
//{
//	t_token	*token;

//	token = (t_token *)malloc(sizeof(t_token));
//    token->tkn_idx = idx;
//    token->token_type = type;
//    token->qt_status = qt_status;
//    token->value = strdup(value);
//    token->next = NULL;
//    token->prev = NULL;

//	return (token);
//}

//void	add_token(t_token **tokens, t_token *new_token)
//{
//	t_token	*tmp;

//	if (*tokens == NULL)
//		*tokens = new_token;
//	else
//	{
//		tmp = *tokens;
//		while (tmp->next != NULL)
//			tmp = tmp->next;
//		tmp->next = new_token;
//		new_token->prev = tmp;
//	}
//}

//void	tokenize(const char *input, t_token **tokens)
//{
//	int	state;
//	char	current_token[256];
//	int	token_index;
//	int	current_token_length;
//	//t_lex_tbl	token_type;
//	int	i;
//	char	c;

//	state = normal;
//	token_index = 0;
//	current_token_length = 0;
//	i = 0;

//	while (input[i] != '\0')
//	{
//		c = input[i];
//		if (state == normal)
//		{
//			if (ft_isspace(c))
//			{
//				if (current_token_length > 0)
//				{
//					current_token[current_token_length] = '\0';
//					add_token(tokens, creat_token(token_index++, l_word, normal, current_token));
//					current_token_length = 0;
//				}
//			}
//		}
//		i++;
//	}
//}


void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->len = 0;
}

void	ft_add_token(char *prompt, int cnt, t_tkn_stk **tkns)
{
	t_token	*tok;
	t_token	*tmp;

	tok = (t_token *)ft_calloc(sizeof(t_token), 1);
	tok->value = ft_substr(prompt, 0, cnt);
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
		{
			if (i + 1 < len && ft_is_metachar(prompt[i + 1]))
			{
				if ((prompt[i] == '>' && prompt[i + 1] == '>') || \
				(prompt[i] == '<' && prompt[i + 1] == '<') || \
				(prompt[i] == '|' && prompt[i + 1] == '|') || \
				(prompt[i] == '&' && prompt[i + 1] == '&'))
				{
					ft_add_token(prompt + i, 2, &tokens);
					i += 2;
					continue;
				}
			}
			ft_add_token(prompt + i++, cnt, &tokens);
		}
		else if (prompt[i] == '"')
		{
			while (prompt[i + cnt] != '"')
				cnt++;
			ft_add_token(prompt + i, ++cnt, &tokens);
			i += cnt;
		}
		else
		{
			while (!ft_isspace(prompt[i + cnt]))
				cnt++;
			ft_add_token(prompt + i, ++cnt, &tokens);
			i += cnt;
		}
	}
	return (tokens);
}
