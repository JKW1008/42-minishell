/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:33:08 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 21:22:11 by kjung            ###   ########.fr       */
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

void	envp_update_while(char **envp, char **old_pwd, char *pwd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			*old_pwd = ft_strdup(envp[i] + 4);
			free(envp[i]);
			envp[i] = ft_strjoin("PWD=", pwd);
		}
		else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			free(envp[i]);
			if (*old_pwd)
				envp[i] = ft_strjoin("OLDPWD=", *old_pwd);
			else
				envp[i] = ft_strdup("OLDPWD=");
		}
		i++;
	}
}
