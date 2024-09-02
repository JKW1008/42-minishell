/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/02 16:06:43 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_qt_value(t_token *tkn)
{
	int	len;

	len = ft_strlen(tkn->value);
	ft_memmove(tkn->value, tkn->value + 1, len - 2);
	tkn->value[len - 2] = 0;
	tkn->value[len - 1] = 0;
}

size_t	 ft_lexer(t_data **data)
{
	t_token		*current;

	(*data)->tkn = ft_tokenize((*data)->prompt);
	if (!(*data)->tkn)
		return (ft_print_ret("minishell: Tokenization failed\n", 2));
	current = (*data)->tkn->head;
	while (current)
	{
		ft_identify_token_type(current, (*data)->envp);
		if (current->qt_status != normal)
			ft_set_qt_value(current);
		printf("val:%s\n", current->value);
		current = current->next;
	}
	return (0);
}
