/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/09/02 15:53:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
t_ast_node	*create_node(t_node_type type, t_token *tkn)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		write(STDERR_FILENO, "Allocation Failed\n", 19);
		exit(EXIT_FAILURE);
	}
	node->type = type;
	node->value = ft_strdup(tkn->value);
	node->tkn_idx = tkn->tkn_idx;
	node->qt_status = tkn->qt_status;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*ft_find_pipe(t_data **data, int num)
{
	t_token		*current;

	current = (*data)->tkn->head;
	while (current->tkn_idx < num)
		 current = current->next;
	while (current || current->token_type != l_pipe)
		current = current->next;
	if (!current)
		return (NULL);
	else
		return (create_node(NODE_PIPE, current));
}

t_ast_node ast_command(t_data **data)
{

}

int ft_creat_left(t_data **data, t_ast_node *head)
{
	return (1);
}

t_ast_node	*parse(t_data **data)
{
	t_ast_node *root;

	head_node = ft_find_pipe(data, 0);
	if (head_node)
		;

}

size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	ms_execute(data);
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}
