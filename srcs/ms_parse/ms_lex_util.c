/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lex_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:12:56 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:49:06 by kjung            ###   ########.fr       */
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
	int			i;
	const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(token, builtins[i], 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_redirection(const char *token)
{
	return (ft_strncmp(token, "<", 2) == 0 || \
			ft_strncmp(token, ">", 2) == 0 || \
			ft_strncmp(token, ">>", 2) == 0);
}
