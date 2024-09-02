/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/29 16:25:53 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prompt(t_data **data)
{
	char	*input;

	while (1)
	{
		//printf("%s%s%c ", "MINISHELL:", (*data)->current_path, '>');
		input = readline("$ ");
		if (!input)
			break;
		(*data)->prompt = input;
		ft_parser(data);
		if (ft_strlen(input))
			add_history(input);
		ms_execute(data);
		free(input);
	}
	return ;
}
