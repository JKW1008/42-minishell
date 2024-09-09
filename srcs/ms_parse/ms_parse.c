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
 
//int	ft_init_cmdline(t_data **data)
//{
//	t_cmdline *cmdline;

//	cmdline = (t_cmdline *) malloc(sizeof(t_cmdline));
//	if (!cmdline)
//		return (1);
//	cmdline->count = 0;
//	cmdline->head = NULL;
//	(*data)->cmdline = cmdline;
//	return (0);
//}

//int	ft_cmd_simplecmd(t_cmd *cmd, t_token *tkn)
//{
//	t_token *current;
//	int		counter;
	
//	cmd->args = (t_args **) malloc(sizeof(t_args *));
//	current = tkn;
//	while (tkn->token_type == l_word || tkn->next)
//		tkn = tkn->next;
//	counter = current->tkn_idx - tkn->tkn_idx;
//}

//int ft_alloc_rdr(t_cmd *cmd, t_token *tkn)
//{
//	int cnt;
	
//	cnt = 0;
//	while (tkn->token_type != l_pipe && tkn->next)
//	{
//		if (tkn->token_type >= 4 && tkn->token_type <= 7)
//			cnt++;
//		tkn = tkn->next;
//	}
//	cmd->rdr = (t_args *) malloc(sizeof(t_args) * cnt);
//	if (!cmd->args)
//		exit(EXIT_FAILURE);
//	return (cnt);
//}

//int	ft_get_rdr(t_cmd *cmd, t_token *tkn)
//{
		
//}

//int	ft_cmd_rdr(t_cmd *cmd, t_token *tkn)
//{
//	int	idx;
//	int	cnt;

//	idx = 0;
//	cnt = ft_alloc_rdr(cmd, tkn);
//	while (idx < cnt)
//	{
		
//	}


//}

//int	ft_create_cmd(t_data **data, t_token **tkn)
//{
//	t_cmd	*cmd;
//	struct	idx;
	

//	cmd = (t_cmd *) malloc(sizeof(t_cmd));
//	if (!cmd)
//		exit(EXIT_FAILURE);
//	ft_alloc_rdr(cmd, tkn);
//	while ((*tkn)->token_type != l_pipe && (*tkn)->next)
//	{
//		if ((*tkn)->token_type >= 4 && (*tkn)->token_type <= 7)
//			ft_cmd_rdr(cmd, (*tkn));
//		else if ((*tkn)->token_type == l_word)
//			ft_cmd_simplecmd(cmd, (*tkn));
//	}
//	return (0);
//}

// int	parse(t_data **data)
// {
// 	t_token *tkn;

// 	tkn = (*data)->tkn->head;
//	while (tkn)
//		ft_create_cmd(data, &tkn);
	
//	return (0);
// }


size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	parse(data);
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}
