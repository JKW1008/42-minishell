/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/10/17 23:13:35 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmdline	*ft_init_cmdline(void)
{
	t_cmdline	*cmdline;

	cmdline = (t_cmdline *) malloc(sizeof(t_cmdline));
	if (!cmdline)
		return (NULL);
	cmdline->count = 0;
	cmdline->head = NULL;
	return (cmdline);
}

static size_t	ft_check_tknlen(t_token *tkn)
{
	t_token	*tmp;
	size_t	token_count;

	tmp = tkn;
	token_count = 0;
	if (tmp->token_type == l_pipe && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->token_type != l_pipe)
	{
		tmp = tmp->next;
		token_count++;
	}
	return (token_count);
}

static int	token_move(t_token **tkn, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		(*tkn) = (*tkn)->next;
		idx++;
	}
	return (0);
}

static size_t	parse(t_data **data)
{
	t_token	*tkn;
	t_cmd	*cmd;
	int		tkn_counter;

	(*data)->cmdline = ft_init_cmdline();
	tkn = (*data)->tkn->head;
	while (tkn && tkn->tkn_idx < (*data)->tkn->len)
	{
		if (tkn->token_type != l_pipe && tkn->tkn_idx != (*data)->tkn->len)
		{
			tkn_counter = ft_check_tknlen(tkn);
			if (tkn_counter == 0)
				return (2);
			cmd = ft_create_cmd(&tkn, data);
			if (!cmd)
				return (1);
			ft_append_cmd(cmd, (*data)->cmdline);
			token_move(&tkn, tkn_counter);
		}
		else if (tkn->next)
			tkn = tkn->next;
		else
			return (0);
	}
	return (0);
}

size_t	ft_parser(t_data **data)
{	
	(*data)->errno_ = 0;
	(*data)->errno_ = ft_lexer(data);
	(*data)->errno_ = ft_merge_tokens(data);
	(*data)->errno_ = parse(data);
	(*data)->errno_ = ft_sort_ord(data);
	if ((*data)->errno_)
		ft_global_err((*data)->errno_, 1);
	if ((*data)->errno_ || ft_global_err(0, 0))
		printf("minishell: syntax error\n");
	else
		ft_global_err(0, 1);
	return (0);
}
