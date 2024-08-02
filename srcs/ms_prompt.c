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

static char	*ft_prompt_name(void)
{
	char *prompt;
	
	prompt = ft_strjoin("MINISHELL @", getcwd(NULL, 1024));
	prompt = ft_strjoin(prompt, ": ");
	return (prompt);
}

void	ft_prompt(void)
{
	char	*input;
	char	*shell_prompt;

	while (1)
	{
		shell_prompt = ft_prompt_name();
		input = readline(shell_prompt);
	}
}