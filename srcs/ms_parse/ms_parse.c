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

//int	ft_cmd_rdr(t_cmd *cmd, t_token *tkn)
//{
//	// 먼저 리다이렉션 갯수 세야함
//}

//int	ft_create_cmd(t_data **data, t_token *tkn, int counter)
//{
//	t_cmd	*cmd;

//	cmd = (t_cmd *) malloc(sizeof(t_cmd));
//	if (!cmd)
//		exit(EXIT_FAILURE);
//	if (tkn->token_type >= 4 || tkn->token_type <= 7)
//		ft_cmd_rdr(cmd, tkn);
//	else if (tkn->token_type == l_word)
//		ft_cmd_simplecmd(cmd, tkn);
//	return (0);
//}

// int	parse(t_data **data)
// {
// 	t_token *tkn;
// 	t_token	*current;
// 	int		counter;

// 	tkn = (*data)->tkn->head;
// 	current = tkn;
// }


size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}
