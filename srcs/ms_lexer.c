/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/04 16:46:01 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_valid_quotes(char *prompt)
{
	int	i;
	int	single_qt;
	int	double_qt;

	i = 0;
	single_qt = 0;
	double_qt = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
			single_qt++;
		else if (prompt[i] == '"')
			double_qt++;
		i++;
	}
	if (single_qt % 2 || double_qt % 2)
		return (1);
	return (0);
}


void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->len = 0;
}

size_t	ft_lexer(char *prompt)
{
	t_tkn_stk	*tokens;

	ft_init_stk_tokens(&tokens);
	if (ft_valid_quotes(prompt))
	{
		printf("minishell: Invalid quotes\n");
		return (1);
	}
	return (0);
}
