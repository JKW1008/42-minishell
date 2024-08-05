/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/07/31 16:06:54 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	ft_prompt(void)
{
	char	*input;

	while (1)
	{
		//printf("%s%s%c ", "MINISHELL:", (*data)->current_path, '>');
		input = readline("$ ");
		if (!input)
			break;
		//ft_parser(input);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	return ;
}
