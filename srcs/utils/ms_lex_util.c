/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lex_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:12:56 by kjung             #+#    #+#             */
/*   Updated: 2024/09/05 21:51:14 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_command(const char *token, char **envp)
{
	char	*path;

	path = find_path(envp, (char *)token);
	if (path)
	{
		free(path);
		return (1);
	}
	return (0);
}

int	ft_is_builtin(const char *token)
{
	const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(token, builtins[i], 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int ft_is_redirection(const char *token)
{
	return (ft_strncmp(token, "<", 2) == 0 || 
			ft_strncmp(token, ">", 2) == 0 || 
			ft_strncmp(token, ">>", 2) == 0);
}
void	ft_identify_token_type(t_token *token, char **envp)
{
    size_t len;

	len = ft_strlen(token->value);
	if (ft_is_builtin(token->value))
		token->token_type = l_word;
	else if (ft_is_command(token->value, envp))
		token->token_type = l_word;
	else if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
		token->token_type = l_quot_dbl;
	else if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
		token->token_type = l_quot_sgl;
	else if (ft_strncmp(token->value, "|", 1) == 0)
		token->token_type = l_pipe;
	else if (ft_strncmp(token->value, "<", 1) == 0)
		token->token_type = l_less;
	else if (ft_strncmp(token->value, ">", 1) == 0)
		token->token_type = l_greater;
	else if (ft_strncmp(token->value, "<<", 2) == 0)
		token->token_type = l_dbl_less;
	else if (ft_strncmp(token->value, ">>", 2) == 0)
		token->token_type = l_dbl_greater;
	else if (ft_strncmp(token->value, "`", 1) == 0)
		token->token_type = l_bck_tick;
	else if (ft_strncmp(token->value, "\\", 1) == 0)
		token->token_type = l_bck_slash;
	else if (ft_strncmp(token->value, ";", 1) == 0)
		token->token_type = l_semicolon;
	else if (ms_ft_isspace(token->value[0]))
		token->token_type = l_space;
	else if (token->value[0] == '#')
		token->token_type = l_comment;
	else if (ft_strncmp(token->value, "&", 1) == 0)
		token->token_type = l_ampersand;
	else if (ft_strncmp(token->value, "(", 1) == 0)
		token->token_type = l_popen;
	else if (ft_strncmp(token->value, ")", 1) == 0)
		token->token_type = l_pclose;
	else
		token->token_type = l_word;
}

t_tkn_stk	*ft_free_tokens(t_tkn_stk *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(tokens);
	return (NULL);
}
