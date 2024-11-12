/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	in_prompt(t_data **data, char *input, t_heredoc_list *list)
{
	add_history(input);
	(*data)->prompt = ft_strdup(input);
	if ((*data)->prompt == NULL)
		ft_error("Memory allocation failed");
	ft_parser(data);
	process_commands(data, list);
	execute_pipeline(data, list);
	free((*data)->prompt);
	(*data)->prompt = NULL;
}

void	ft_prompt(t_data **data)
{
	char			*input;
	t_heredoc_list	heredoc_list;
	int				i;

	ft_memset(&heredoc_list, 0, sizeof(t_heredoc_list));
	while (1)
	{
		ft_global_err(0, 1);
		input = readline("$ ");
		if (!input)
			break ;
		(*data)->prompt = input;
		if (ft_strlen(input) > 0)
			in_prompt(data, input, &heredoc_list);
		free(input);
		i = 0;
		while (i < heredoc_list.count)
		{
			free(heredoc_list.heredocs[i].content);
			free(heredoc_list.heredocs[i].delimiter);
			i++;
		}
		ft_memset(&heredoc_list, 0, sizeof(t_heredoc_list));
		ft_destroy_parser_context(data);
	}
	return ;
}
