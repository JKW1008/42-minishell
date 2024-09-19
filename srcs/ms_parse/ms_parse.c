/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/09/06 15:54:03 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
int	ft_init_cmdline(t_data **data)
{
	t_cmdline *cmdline;

	cmdline = (t_cmdline *) malloc(sizeof(t_cmdline));
	if (!cmdline)
		return (1);
	cmdline->count = 0;
	cmdline->head = NULL;
	(*data)->cmdline = cmdline;
	return (0);
}
int ft_alloc_rdr(t_cmd *cmd, t_token *tkn)
{
	int cnt;
	int idx;
	 
	cnt = 0;
	idx = 0;
	while (tkn->token_type != l_pipe && tkn->next)
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
//char *ft_get_envp_arg(char *val, t_data **data)
//{
//	int	i;
//	char **tmp;

//	i = 0;
//	while ((*data)->envp[i])
//	{
//		tmp = ft_split((*data)->envp[i], '=');
//		i++;
//	}
//}

int	ft_get_args(t_cmd *cmd, t_token *tkn, t_data **data)
{
	int idx;

	idx = 0;
	while (idx < cmd->arg_cnt)
	{
		cmd->args[idx].og = ft_strdup(tkn->value);
		cmd->args[idx].ex = ft_strdup(tkn->value);
		printf("%d\n", (*data)->tkn->head->tkn_idx);
		//if (tkn->qt_status == in_single)
		//	cmd->args[idx]->ex = ft_strdup(tkn);
		//else
		//	cmd->args[idx]->ex = ft_parse_arg(tkn->value);
		tkn = tkn->next;
		idx++;
	}
	return (idx);
}

int	ft_alloc_simplecmd(t_cmd *cmd, t_token *tkn, t_data **data)
{
	while (tkn && tkn->token_type != l_pipe)
	{
		if (tkn->token_type >= 4 && tkn->token_type <= 7)
		{
			tkn = tkn->next;
			tkn = tkn->next;
		}
		if (tkn && tkn->token_type == l_word)
		{
			if (cmd->cmd == NULL)
			{
				cmd->cmd = ft_strdup(tkn->value);
				if (tkn->next)
					tkn = tkn->next;
				else
					return (0);
			}
			else
			{
				t_token	*tmp = tkn;
				while (tmp->token_type == l_word)
				{
					cmd->arg_cnt++;
					if (!tmp->next)
						break;
					tmp = tmp->next;
				}
				if (cmd->arg_cnt == 0)
					return  (0);
				cmd->args = (t_args *) malloc(sizeof(t_args) * (cmd->arg_cnt + 1));
				int count = ft_get_args(cmd, tkn, data);
				while (count--)
					tkn = tkn->next;
				if (!tkn)
					return(0);
			}
		}
		else
			return (1);
	}
	return (0);
}

int	ft_get_rdr(t_cmd *cmd, t_token **tkn, int idx)
{
	if ((*tkn)->token_type == l_less)
		cmd->rdr[idx]->type = RD_IN;
	else if ((*tkn)->token_type == l_greater)
		cmd->rdr[idx]->type = RD_OUT;
	else if ((*tkn)->token_type == l_dbl_less)
		cmd->rdr[idx]->type = RD_HEREDOC;
	else if ((*tkn)->token_type == l_dbl_greater)
		cmd->rdr[idx]->type = RD_APPEND;
	(*tkn) = (*tkn)->next;
	cmd->rdr[idx]->file = ft_strdup((*tkn)->value);
	return (0);
}

int	ft_cmd_rdr(t_cmd *cmd, t_token *tkn)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = ft_alloc_rdr(cmd, tkn);
	if (!cnt)
		return (0);
	while (idx < cnt)
	{
		while (tkn->token_type >= 4 && tkn->token_type <= 7)
			tkn = tkn->next;
		ft_get_rdr(cmd, &tkn->prev, idx++);
		tkn = tkn->next;
	}
	return (0);

}

t_cmd	*ft_create_cmd(t_token **tkn, t_data **data)
{
	t_cmd	*cmd;
	struct	idx;
	
	cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		exit(EXIT_FAILURE);
	if ((*tkn)->token_type == l_pipe)
		(*tkn) = (*tkn)->next;
	ft_alloc_rdr(cmd, *tkn);
	ft_alloc_simplecmd(cmd, *tkn, data);
	return (cmd);
}

int	parse(t_data **data)
{
 	t_token *tkn;
	t_cmd 	*new;
	t_cmd	*cmd;

	(*data)->cmdline = ft_calloc(sizeof(t_cmdline), 1);
 	tkn = (*data)->tkn->head;
	while (tkn->tkn_idx < (*data)->tkn->len)
	{
		if (tkn->tkn_idx == 0 || tkn->token_type == l_pipe)
		{
			new = ft_create_cmd(&tkn, data);
			if ((*data)->cmdline->head)
			{
				cmd = (*data)->cmdline->head;
				while (cmd->next)
					cmd = cmd->next;
				cmd->next = new;
			}
			else
				(*data)->cmdline->head = new;
		}
		if (tkn->next)
			tkn = tkn->next;
		else
			return (0);
	}
	return (0);
 }

size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	parse(data);
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}
