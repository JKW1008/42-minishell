/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:14:33 by kjung             #+#    #+#             */
/*   Updated: 2024/10/17 01:03:27 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_valid_quotes(char *prompt)
{
	int	len;

	len = ft_strlen(prompt);
	if (prompt[0] == '\'' || prompt[0] == '"')
	{
		if (len < 2)
			return (1);
		if (prompt[0] == '\'' && prompt[len - 1] != '\'')
			return (1);
		if (prompt[0] == '"' && prompt[len - 1] != '"')
			return (1);
	}
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
			ft_add_token(prompt, 0, 2, tkns);
			return (2);
		}
	}
	ft_add_token(prompt, 0, 1, tkns);
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
	ft_add_token(prompt, 0, ++i, tkns);
	return (i);
}
