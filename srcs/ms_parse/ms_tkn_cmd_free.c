/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tkn_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:18:23 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/17 01:03:25 by kjung            ###   ########.fr       */
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
