/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:48:28 by kjung             #+#    #+#             */
/*   Updated: 2024/08/11 18:23:27 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_process_env_var(char **expanded, char **start, char **evnp);

char	*ft_replace_substring(char *str, char *start, char *end, char *replacement)
{
	size_t	prefix_len;
	size_t	suffix_len;
	size_t	replacement_len;
	size_t	new_len;
	char	*new_str;

	prefix_len = start - str;
	suffix_len = ft_strlen(end);
	replacement_len = ft_strlen(replacement);
	new_len = prefix_len + replacement_len + suffix_len;
	new_str = (char *)malloc(new_len + 1);
	if (!new_str)
		return NULL;
	ft_memcpy(new_str, str, prefix_len);
	ft_memcpy(new_str + prefix_len, replacement, replacement_len);
	ft_memcpy(new_str + prefix_len + replacement_len, end, suffix_len);
	new_str[new_len] = '\0';
	return new_str;
}

size_t ft_expand_env_vars(t_token *token, char **envp)
{
	char	*expanded;
	char	*start;

	expanded = ft_strdup(token->value);
	if (!expanded)
		return (1);
	start = expanded;
	while ((start = ft_strchr(start, '$')))
	{
		if (ft_process_env_var(&expanded, &start, envp))
		{
			free(expanded);
			return (1);
		}
	}
	free(token->value);
	token->value = expanded;
	return (0);
}

size_t	ft_process_env_var(char **expanded, char **start, char **envp)
{
	char	*end;
    char	*var_name;
    char	*var_value;
	char	*new_str;
    int		i;

	var_value = NULL;
	end = *start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	var_name = ft_substr(*start + 1, 0, end - *start - 1);
	if (!var_name)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 
			&& envp[i][ft_strlen(var_name)] == '=')
		{
			var_value = envp[i] + ft_strlen(var_name) + 1;
			break;
		}
	}
	new_str = ft_replace_substring(*expanded, *start, end, var_value ? var_value : "");
	free(*expanded);
	*expanded = new_str;
	if (!*expanded)
	{
		free(var_name);
		return (1);
	}
	free(var_name);
	*start = *expanded + (*start - *expanded);
	return (0);
}

size_t ft_validate_token_structure(t_tkn_stk *tokens)
{
	t_token	*current;
	int		cmd_found;
	int		pipe_count;

	current = tokens->head;
	cmd_found = 0;
	pipe_count = 0;
	while (current)
	{
		if (current->token_type == l_pipe)
		{
			if (!cmd_found || !current->next)
				return (1);
			cmd_found = 0;
			pipe_count++;
		}
		else if (current->token_type == l_less || current->token_type == l_greater ||
					current->token_type == l_dbl_less || current->token_type == l_dbl_greater)
		{
			if (!current->next || current->next->token_type != l_word)
				return (2);
		}
		else if (current->token_type == l_word)
			cmd_found = 1;
		current = current->next;
	}
	if (pipe_count > 0 && !cmd_found)
		return (3);
	return (0);
}
