/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sort_ord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:14:04 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/30 18:14:12 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parse.h"

size_t	ft_sort_ord(t_data **data)
{
	int	i;
	int	ord;
	t_cmd	*cmd;

	i = 0;
	ord = 1;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->is_heredoc && cmd->ord == 0)
			cmd->ord = ord++;
		cmd = cmd->next;
		i++;
	}
	i = 0;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->is_builtin && cmd->ord == 0)
			cmd->ord = ord++;
		cmd = cmd->next;
		i++;
	}
	i = 0;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->ord == 0)
			cmd->ord = ord++;
		cmd = cmd->next;
		i++;
	}
	return (0);
}
