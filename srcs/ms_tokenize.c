/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:03:33 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/08 21:59:03 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*creat_token(int idx, t_lex_tbl type, t_quote_tbl qt_status, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
    token->tkn_idx = idx;
    token->token_type = type;
    token->qt_status = qt_status;
    token->value = strdup(value);
    token->next = NULL;
    token->prev = NULL;
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == ';');
}

void	tokenize(const char *input, t_token **tokens)
{
	int	state;
	char	current_token[256];
	int	token_index;
	int	current_token_length;
	t_lex_tbl	token_type;
	int	i;
	char	c;

	state = normal;
	token_index = 0;
	current_token_length = 0;
	i = 0;

	while (input[i] != '\0')
	{
		c = input[i];

		if (state == normal)
		{
			if (ft_isspace(c))
			{
				if (current_token_length > 0)
				{
					current_token[current_token_length] = '\0';
					add_token(tokens, creat_token(token_index++, l_word, normal, current_token));
					current_token_length = 0;
				}
			}
		}
		i++;
	}
}

t_tkn_stk	ft_tokenize(char *prompt)
{
	printf("%s\n", prompt);
}