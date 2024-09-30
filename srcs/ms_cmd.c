/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 08:16:34 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//char	*setup_here_doc(t_cmd *cmd)
//{

//}

void	find_heredoc(t_cmd *token)
{
	t_cmd	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->is_heredoc)
			
		tmp = tmp->next;
	}
	return ;
}

void	ms_cmd(t_data **data)
{
	 t_cmd	*tmp;
	 int		i;

	const char* redir_type_strings[] = { \
    	[RD_IN] = "RD_IN", \
    	[RD_OUT] = "RD_OUT", \
    	[RD_APPEND] = "RD_APPEND", \
    	[RD_HEREDOC] = "RD_HEREDOC", \
    	[RD_EOF] = "RD_EOF"}; 

	 tmp = (*data)->cmdline->head;
	 while (tmp)
	 {
	 	printf("ord = %d\n", tmp->ord);
		if (tmp->cmd)
	 		printf("cmd = %s\n", tmp->cmd);
	 	printf("in_here_doc = %d\n", tmp->is_heredoc);
	 	printf("is_builtin = %d\n", tmp->is_builtin);
	 	i = 0;
	 	while (i < tmp->arg_cnt)
	 	{
	 		printf("args[%d] = %s\n", i, tmp->args[i]);
	 		i++;
	 	}
		for (int i = 0; i < tmp->rdr_cnt; i++)
    		printf("rdr[%d]: %s %s\n", i, redir_type_strings[tmp->rdr[i]->type], tmp->rdr[i]->file);
		tmp = tmp->next;
		printf("-------------------------------------------\n");
	 }
	 printf("-------------------------------------------\n");
	
}
