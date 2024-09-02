/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/09/02 15:00:17 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_node(t_node_type type, char *value)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(t_ast_node));
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_command(t_token **current)
{
	t_ast_node	*cmd_node;
	t_ast_node	*arg_node;

	cmd_node = create_node(NODE_COMMAND, (*current)->value);
	*current = (*current)->next;
	while (*current && (*current)->token_type == l_word)
	{
		arg_node = create_node(NODE_ARGUMENT, (*current)->value);
		arg_node->left = cmd_node->left;
		cmd_node->left = arg_node;
		*current = (*current)->next;
	}
	return (cmd_node);
}

t_ast_node	*parse_pipeline(t_token **current)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;
	t_ast_node	*right;

	left = parse_command(current);
	while (*current && (*current)->token_type == l_pipe)
	{
		pipe_node = create_node(NODE_PIPE, "|");
		*current = (*current)->next;
		right = parse_command(current);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

t_ast_node	*parse(t_data **data)
{
    t_token *current;

	current = (*data)->tkn->head;
	if (ft_validate_token_structure((*data)->tkn))
	{
		printf("minishell: Invalid token structure\n");
		ft_free_tokens((*data)->tkn);
		return (0);
	}
	ft_free_tokens((*data)->tkn);
    return (parse_pipeline(&current));
}

size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}