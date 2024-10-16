/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sort_ord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:14:04 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/16 22:20:05 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_ord_heredoc(t_data **data, int *ord)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->is_heredoc && cmd->ord == 0)
			cmd->ord = (*ord)++;
		cmd = cmd->next;
		i++;
	}
}

void	ft_sort_ord_builtin(t_data **data, int *ord)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->is_builtin && cmd->ord == 0)
			cmd->ord = (*ord)++;
		cmd = cmd->next;
		i++;
	}
}

void	ft_sort_ord_cnt(t_data **data, int *ord)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (*data)->cmdline->head;
	while (i < (*data)->cmdline->count)
	{
		if (cmd->ord == 0)
			cmd->ord = (*ord)++;
		cmd = cmd->next;
		i++;
	}
}

size_t	ft_sort_ord(t_data **data)
{
	int		ord;

	ord = 1;
	ft_sort_ord_heredoc(data, &ord);
	ft_sort_ord_builtin(data, &ord);
	ft_sort_ord_cnt(data, &ord);
	return (0);
}
