/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/10 18:47:22 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_heredoc(t_cmd *node)
{
	char	*result;
	
	return (result);
}

void	call_builtin(t_data **data)
{
	t_cmd	*tmp;
	char	*here_doc;

	tmp = (*data)->cmdline->head;
	while (tmp && tmp->prompt)
	{
		if (tmp->is_builtin)
			ms_execute(tmp, data);
		else if (tmp->is_heredoc)
			here_doc = set_heredoc(tmp);
		tmp = tmp->next;
	}
}

void	ft_prompt(t_data **data)
{
	char	*input;

	while (1)
	{
		input = readline("$ ");
		if (!input)
			break ;
		(*data)->prompt = input;
		if (ft_strlen(input))
		{
			ft_parser(data);
			call_builtin(data);
			// ms_cmd(data);
			add_history(input);
		}
		free(input);
	}
	return ;
}
