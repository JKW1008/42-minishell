/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:06:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/15 16:19:49 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

char	*set_heredoc(t_cmd *node)
{
	char	*line;
	char	*result;
	char	*new_result;
	size_t	res_len;
	size_t	res_cap;

	result = NULL;
	res_len = 0;
	res_cap = 0;
	while (1)
	{
		line = get_input("> ");
		if (!line || ft_strncmp(line, node->args[0], ft_strlen(node->args[0]) == 0))
		{
			free(line);
			break;
		}
		if (res_len + ft_strlen(line) + 2 > res_cap)
		{
			if (res_cap == 0)
				res_cap = 1024;
			else
				res_cap = res_cap * 2;
			new_result = realloc(result, res_cap);
			if (!new_result)
			{
				free(result);
				free(line);
				return (NULL);
			}
			result = new_result;
		}
		ft_strlcpy(result + res_len, line, ft_strlen(line));
		res_len += ft_strlen(line);
		result[res_len++] = '\n';
		result[res_len] = '\0';
		free(line);
	}
	return (result);
}

void	call_builtin(t_data **data)
{
	t_cmd	*tmp;
	char	*here_doc;

	tmp = (*data)->cmdline->head;
	while (tmp && tmp->prompt)
	{
		printf("here_doc = %s\n", tmp->cmd);
		if (tmp->is_builtin)
		{
			ms_execute(tmp, data);
		}
		else if (tmp->is_heredoc)
		{
			here_doc = set_heredoc(tmp);
			printf("%s\n", here_doc);
		}
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
