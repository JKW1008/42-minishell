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



size_t	 ft_lexer(t_data **data)
{
	t_token		*current;

	//if (ft_valid_quotes((*data)->prompt))
	//	return (ft_print_ret("minishell: Invalid quotes\n", 1));
	(*data)->tkn = ft_tokenize((*data)->prompt);
	if (!(*data)->tkn)
		return (ft_print_ret("minishell: Tokenization failed\n", 2));
	current = (*data)->tkn->head;
	while (current)
	{
		ft_identify_token_type(current, (*data)->envp);
		current = current->next;
	}
	return (0);
}
