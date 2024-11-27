/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/26 22:11:26 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_set_prompt_pwd(void)
{
	char	*pwd;
	char	*new_pwd;

	pwd = getcwd(NULL, BUFSIZ);
	new_pwd = ft_strjoin("$", pwd);
	free(pwd);
	pwd = ft_strjoin(new_pwd, " ");
	free(new_pwd);
	return (pwd);
}

void	in_prompt(t_data **data, char *input)
{
	if (ft_strlen(input) < 1)
		return ;
	add_history(input);
	(*data)->prompt = ft_strdup(input);
	if ((*data)->prompt == NULL)
		ft_error("Memory allocation failed");
	ft_parser(data);
	if (ft_global_err(0, 0) != 0)
		return ;
	process_heredoc(data);
	execute_pipeline(data);
}

void	ft_prompt(t_data **data)
{
	char			*input;
	char			*pwd;

	while (1)
	{
		ft_global_err(0, 3);
		pwd = ft_set_prompt_pwd();
		input = readline(pwd);
		if (!input)
			break ;
		(*data)->prompt = input;
		in_prompt(data, input);
		ft_destroy_parser_context(data);
		free(pwd);
	}
	free(pwd);
	return ;
}
