/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:33 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_print_ret(char *msg, int value)
{
	printf("%s", msg);
	return (value);
}

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

size_t	ft_lexer(t_data **data)
{
	t_tkn_stk	*tokens;
	t_token		*current;
	size_t		error_code;

	error_code = 0;
	if (ft_valid_quotes((*data)->prompt))
		return (ft_print_ret("minishell: Invalid quotes\n", 1));
	tokens = ft_tokenize((*data)->prompt);
	if (!tokens)
		return (ft_print_ret("minishell: Tokenization failed\n", 2));
	(*data)->tkn = tokens;
	current = tokens->head;
	while (current)
	{
		ft_identify_token_type(current, (*data)->envp);
		if (current->token_type == l_word)
		{
			if (ft_expand_env_vars(current, (*data)->envp))
			{
				printf("minishell: Error in environment variable expansion\n");
				ft_free_tokens(tokens);
				return (error_code);
			}
		}
		current = current->next;
	}
	return (0);
}
