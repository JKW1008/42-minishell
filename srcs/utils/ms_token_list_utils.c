/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:39:30 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 02:18:12 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_process_special_chars(char *prompt, int *i, t_tkn_stk **tkns)
{
	int	cnt;

	if (ms_ft_isspace(prompt[*i]))
	{
		(*i)++;
		return (0);
	}
	else if (ft_is_metachar(prompt[*i]))
	{
		cnt = ft_token_metachar(prompt + *i, tkns);
		if (cnt == -1)
			return (-1);
		*i += cnt;
	}
	else if (prompt[*i] == '"' || prompt[*i] == '\'')
	{
		cnt = ft_token_quote(prompt + *i, tkns, prompt[*i]);
		if (cnt == -1)
			return (-1);
		*i += cnt;
	}
	return (0);
}

int	ft_process_word(char *prompt, int *i, int len, t_tkn_stk **tkns)
{
	int	cnt;

	cnt = 0;
	while (*i + cnt < len && !ft_is_metachar(prompt[*i + cnt]) && \
			prompt[*i + cnt] != '\'' && prompt[*i + cnt] != '"' && \
			!ms_ft_isspace(prompt[*i + cnt]))
		cnt++;
	if (cnt > 0)
	{
		if (ft_add_token(prompt, *i, cnt, tkns) == -1)
			return (-1);
		*i += cnt;
	}
	return (0);
}

void	ft_tokenize_of_while(char *prompt, int len, t_tkn_stk **tkns)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_process_special_chars(prompt, &i, tkns) == -1)
		{
			ft_free_tokens(*tkns);
			return ;
		}
		if (ft_process_word(prompt, &i, len, tkns) == -1)
		{
			ft_free_tokens(*tkns);
			return ;
		}
	}
}
