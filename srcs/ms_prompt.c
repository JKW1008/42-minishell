/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/29 22:05:00 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prompt(t_data **data)
{
	char	*input;

	while (1)
	{
		input = readline("$ ");
		if (!input)
			break ;
		(*data)->prompt = input;
		ft_parser(data);
		ms_execute((*data)->cmdline->head, data);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	return ;
}
