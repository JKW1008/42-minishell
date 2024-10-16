/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:53:02 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 22:09:52 by kjung            ###   ########.fr       */
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

static int	reallocate_result(char **result, size_t *res_cap, \
size_t needed_size)
{
	char	*new_result;
	size_t	new_cap;

	if (*res_cap == 0)
		new_cap = 1024;
	else
		new_cap = *res_cap * 2;
	while (new_cap < needed_size)
		new_cap *= 2;
	new_result = realloc(*result, new_cap);
	if (!new_result)
		return (0);
	*result = new_result;
	*res_cap = new_cap;
	return (1);
}

static int	process_heredoc_line(t_cmd *node, char **result, \
size_t *res_len, size_t *res_cap)
{
	char	*line;
	size_t	line_len;

	line = get_input("> ");
	if (!line || (ft_strncmp(line, node->args[0], ft_strlen(node->args[0])) \
	== 0 && ft_strlen(line) == ft_strlen(node->args[0])))
	{
		free(line);
		return (0);
	}
	line_len = ft_strlen(line);
	if (*res_len + line_len + 2 > *res_cap)
	{
		if (!reallocate_result(result, res_cap, *res_len + line_len + 2))
		{
			free(line);
			return (0);
		}
	}
	ft_strlcpy(*result + *res_len, line, line_len + 1);
	*res_len += line_len;
	(*result)[(*res_len)++] = '\n';
	(*result)[*res_len] = '\0';
	free(line);
	return (1);
}

char	*set_heredoc(t_cmd *node)
{
	char	*result;
	size_t	res_len;
	size_t	res_cap;

	result = NULL;
	res_len = 0;
	res_cap = 0;
	while (1)
	{
		if (!process_heredoc_line(node, &result, &res_len, &res_cap))
			break ;
	}
	return (result);
}

void	process_commands(t_data **data, t_heredoc_list *heredoc_list)
{
	t_cmd	*tmp;
	char	*here_doc;

	tmp = (*data)->cmdline->head;
	heredoc_list->count = 0;
	while (tmp && tmp->prompt)
	{
		if (tmp->is_heredoc)
		{
			here_doc = set_heredoc(tmp);
			if (here_doc && heredoc_list->count < MAX_HEREDOCS)
			{
				heredoc_list->heredocs[heredoc_list->count].content = here_doc;
				heredoc_list->heredocs[heredoc_list->count].delimiter = \
				ft_strdup(tmp->args[0]);
				heredoc_list->count++;
			}
			else
				free(here_doc);
		}
		tmp = tmp->next;
	}
}
