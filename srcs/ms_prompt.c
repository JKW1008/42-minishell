/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/07 16:54:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_builtin(t_data **data)
{
	t_cmd	*tmp;

	tmp = (*data)->cmdline->head;
	while (tmp && tmp->prompt)
	{
		if (tmp->is_builtin)
			ms_execute(tmp, data);
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
			ms_cmd(data);
			add_history(input);
		}
		free(input);
	}
	return ;
}
