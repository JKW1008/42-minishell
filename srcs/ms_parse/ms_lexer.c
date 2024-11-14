/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/16 21:45:55 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_qt_value(t_token *tkn)
{
	int	len;

	len = ft_strlen(tkn->value);
	ft_memmove(tkn->value, tkn->value + 1, len - 2);
	tkn->value[len - 2] = 0;
	tkn->value[len - 1] = 0;
}

void	ft_set_valex(t_token *tkn, t_data *data)
{
	int		idx;
	char	**tmp_splitted;

	idx = 0;
	if (tkn->qt_status == in_single)
		return ;
	tmp_splitted = ft_split2(tkn->value, '$');
	while (tmp_splitted[idx])
		ft_search_envp(&tmp_splitted[idx++], data);
	free(tkn->value);
	tkn->value = ft_concate(tmp_splitted, 0, 0);
	ft_split_free(&tmp_splitted);
	if (tkn->value && ft_strlen(tkn->value) == 0)
	{
		free(tkn->value);
		tkn->value = NULL;
	}
}

size_t	ft_lexer(t_data **data)
{
	t_token		*current;
	int			idx;

	(*data)->tkn = ft_tokenize((*data)->prompt);
	if (ft_global_err(0, 0))
		return (1);
	if (!(*data)->tkn)
		return (ft_print_ret("minishell: Tokenization failed\n", 2));
	idx = 0;
	current = (*data)->tkn->head;
	while (current)
	{
		ft_identify_token_type(current, (*data)->envp);
		if (current->qt_status != normal)
			ft_set_qt_value(current);
		ft_set_valex(current, *data);
		current->tkn_idx = idx++;
		current = current->next;
	}
	return (0);
}
