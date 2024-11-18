/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/12 17:23:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *ft_set_prompt_pwd(void)
{
	char *pwd;
	char *new_pwd;

	pwd = getcwd(NULL, BUFSIZ);
	new_pwd = ft_strjoin("$", pwd);
	free(pwd);
	pwd = ft_strjoin(new_pwd, " ");
	free(new_pwd);
	return (pwd);
}

void	in_prompt(t_data **data, char *input, t_heredoc_list *list)
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
	process_commands(data);
	execute_pipeline(data, list);

}

void	ft_prompt(t_data **data)
{
	char			*input;
	char			*pwd;
	t_heredoc_list	heredoc_list;

	ft_memset(&heredoc_list, 0, sizeof(t_heredoc_list));
	while (1)
	{
		// ft_ctrl_signal();
		ft_global_err(0, 3);
		pwd = ft_set_prompt_pwd();
		input = readline(pwd);
		if (!input)
			break ;
		(*data)->prompt = input;
		in_prompt(data, input, &heredoc_list);
		ft_destroy_parser_context(data, &heredoc_list);	
		free(pwd);
	}
	ft_destroy_parser_context(data, &heredoc_list);	
	free(pwd);
	return ;
}
