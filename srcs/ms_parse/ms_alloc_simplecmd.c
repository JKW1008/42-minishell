/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alloc_simplecmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:43:49 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/16 21:48:05 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_args(t_cmd *cmd, t_token *tkn)
{
	int		total;
	t_token	*tmp;

	total = 0;
	tmp = tkn;
	while (tmp && tmp->token_type != l_pipe)
	{
		if (tmp->token_type == l_word)
			total++;
		else if (tmp->token_type >= 4 && tmp->token_type <= 7)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	cmd->arg_cnt = total - 1;
	if (cmd->arg_cnt < 0)
		return (1);
	cmd->args = (char **) ft_calloc(sizeof(char **), cmd->arg_cnt + 1);
	return (0);
}

static size_t	get_args(t_cmd *cmd, t_token *tkn)
{
	int		idx;
	t_token	*tmp;

	idx = 0;
	tmp = tkn;
	while (tmp && tmp->token_type != l_word && tmp->token_type != l_pipe)
		tmp = tmp->next;
	if (tmp && tmp->token_type == l_word)
	{
		cmd->cmd = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	while (tmp && tmp->token_type != l_pipe)
	{
		if (tmp->token_type == l_word)
		{
			cmd->args[idx] = ft_strdup(tmp->value);
			idx++;
		}
		else if (tmp->token_type >= 4 && tmp->token_type <= 7)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	cmd->args[idx] = NULL;
	return (idx);
}

int	ft_alloc_simplecmd(t_cmd *cmd, t_token *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	if (count_args(cmd, tmp))
		return (-1);
	get_args(cmd, tmp);
	return (0);
}
