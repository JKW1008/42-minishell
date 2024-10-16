/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alloc_rdr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:09:45 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/16 21:48:30 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parse.h"

static size_t	alloc_rdr(t_cmd *cmd, t_token *tkn)
{
	int	cnt;
	int	idx;

	cnt = 0;
	idx = 0;
	while (tkn && tkn->token_type != l_pipe)
	{
		if (tkn->token_type >= 4 && tkn->token_type <= 7)
			cnt++;
		tkn = tkn->next;
	}
	cmd->rdr = (t_rdr **) malloc(sizeof(t_rdr *) * (cnt + 1));
	if (!cmd->rdr)
		exit(EXIT_FAILURE);
	while (idx < cnt)
	{
		cmd->rdr[idx] = (t_rdr *) malloc(sizeof(t_rdr));
		if (!cmd->rdr[idx])
			exit(EXIT_FAILURE);
		idx++;
	}
	cmd->rdr[idx] = NULL;
	return (cnt);
}

static size_t	get_rdr(t_cmd *cmd, t_token **tkn, int idx)
{
	if ((*tkn)->token_type == l_less)
		cmd->rdr[idx]->type = RD_IN;
	else if ((*tkn)->token_type == l_greater)
		cmd->rdr[idx]->type = RD_OUT;
	else if ((*tkn)->token_type == l_dbl_greater)
		cmd->rdr[idx]->type = RD_APPEND;
	else if ((*tkn)->token_type == l_dbl_less)
	{
		cmd->rdr[idx]->type = RD_HEREDOC;
		cmd->is_heredoc = 1;
	}
	(*tkn) = (*tkn)->next;
	cmd->rdr[idx]->file = ft_strdup((*tkn)->value);
	return (0);
}

int	ft_cmd_rdr(t_cmd *cmd, t_token *tkn)
{
	int		idx;
	int		cnt;
	t_token	*tmp;

	idx = 0;
	tmp = tkn;
	cnt = alloc_rdr(cmd, tmp);
	if (!cnt)
		return (0);
	while (idx < cnt)
	{
		while (tmp->token_type < 4 || tmp->token_type > 7)
			tmp = tmp->next;
		get_rdr(cmd, &tmp, idx++);
		tmp = tmp->next;
	}
	cmd->rdr_cnt = cnt;
	return (0);
}
