/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/07 17:29:48 by kjung            ###   ########.fr       */
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

static t_tkn_stk	*tokenizer(char *prompt, t_tkn_stk **tkns)
{
	int			idx;
	char		**words;
	//t_tkn_stk	*tokns;

	idx = 0;
	if (ft_valid_quotes(prompt))
		printf("minishell: Invalid quotes\n");
	words = ft_split(prompt,  ' ');
	return (*tkns);
}

void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->tail = NULL;
	(*tkns)->__len__ = 0;
}

size_t	ft_lexer(char *prompt)
{
	t_tkn_stk	*tokens;

	ft_init_stk_tokens(&tokens);
	tokens = tokenizer(prompt, &tokens);
	return (0);
}
