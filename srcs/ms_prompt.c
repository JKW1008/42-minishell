/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/08 15:23:53 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	ft_prompt(void)
{
	char	*input;

	while (1)
	{
		//printf("%s%s%c ", "MINISHELL:", (*data)->current_path, '>');
		input = readline("$ ");
		if (!input)
			break;
		ft_tokenize(input);
		// ft_parser(input);
		if (ft_strlen(input))
			add_history(input);
		free(input);
	}
	return ;
}
