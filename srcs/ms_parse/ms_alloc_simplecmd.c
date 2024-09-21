/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alloc_simplecmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:43:49 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/21 10:43:50 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static t_token	*move_next(t_token *tkn, int cnt)
{
	while (cnt--)
		tkn = tkn->next;
	return (tkn);
}

static size_t	count_args(t_cmd *cmd, t_token *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	while (tmp->token_type == l_word)
	{
		cmd->arg_cnt++;
		if (!tmp->next)
			break ;
	}
	return (cmd->arg_cnt);
}

static size_t	get_args(t_cmd *cmd, t_token *tkn)
{
	int	idx;

	idx = 0;
	cmd->args = malloc(sizeof(char *) * (cmd->arg_cnt + 1));
	if (!cmd->args)
		exit(EXIT_FAILURE);
	while (idx < cmd->arg_cnt)
	{
		cmd->args[idx] = ft_strdup(tkn->value);
		tkn = tkn->next;
		idx++;
	}
	cmd->args[idx] = NULL;
	return (idx);
}

static t_token	*get_cmd(t_cmd *cmd, t_token *tkn)
{
	cmd->cmd = ft_strdup(tkn->value);
	if (tkn->next)
		tkn = tkn->next;
	else
		return (NULL);
	return (tkn);
}

int	ft_alloc_simplecmd(t_cmd *cmd, t_token *tkn)
{
	while (tkn && tkn->token_type != l_pipe)
	{
		if (tkn->token_type >= 4 && tkn->token_type <= 7)
			tkn = move_next(tkn, 2);
		if (tkn && tkn->token_type == l_word)
		{
			if (cmd->cmd == NULL)
			{
				tkn = get_cmd(cmd, tkn);
				if (!tkn)
					return (0);
			}
			else
			{
				if (count_args(cmd, tkn) == 0)
					return (0);
				tkn = move_next(tkn, get_args(cmd, tkn));
				if (!tkn)
					return (0);
			}
		}
		else
			return (1);
	}
	return (0);
}
