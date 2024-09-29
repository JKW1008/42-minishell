/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:33:08 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 01:46:56 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_var_name(char *arg, int start, int *end)
{
	int	j;

	j = start + 1;
	while (arg[j] && is_valid_var_char(arg[j]))
		j++;
	*end = j;
	return (ft_substr(arg, start + 1, j - start - 1));
}

char	*join_value(char *result, char *value)
{
	char	*tmp;

	if (value)
		tmp = ft_strjoin(result, value);
	else
		tmp = ft_strdup(result);
	free(result);
	return (tmp);
}
