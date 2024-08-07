/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/06 20:56:51 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prompt(void)
{
	char	*input;
	size_t	i;

	while (1)
	{
		// printf("%s%s%c ", "MINISHELL:", (*data)->current_path, '>');
		input = readline("$ ");
		if (!input)
			break;
		if (!(i = ft_parser(input)))
			ft_error(NULL);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	return ;
}
