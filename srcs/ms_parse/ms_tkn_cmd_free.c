/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tkn_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:18:23 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/23 14:18:25 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_tkn_free(t_token *tkn)
{
	free(tkn->value);
	free(tkn);
	return (0);
}

t_tkn_stk	*ft_free_tokens(t_tkn_stk *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens->head;
	while (current)
	{
		next = current->next;
		ft_tkn_free(current);
		current = next;
	}
	free(tokens);
	return (NULL);
}