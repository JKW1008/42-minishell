/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:34:52 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:41:26 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_name(char *str)
{
   int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export(t_data **data)
{
	char	**cd;
	char	*eq;
	char	*env;
	char	**new_envp;
	int		i;
	int		cnt;
	int		j;

	cd = ft_split((*data)->prompt, ' ');
	if (!cd || !cd[1])
	{
		printenv((*data)->envp, 1);
		free_split(cd);
		return ;
	}
	j = 1;
	while (cd[j])
	{
		eq = ft_strchr(cd[j], '=');
		if (eq)
			env = ft_substr(cd[j], 0, eq - cd[j]);
		else
			env = cd[j];

		if (!is_env_name(env))
		{
			printf("Invalid environment variable name: %s\n", cd[j]);
			free_split(cd);
			if (eq)
				free(env);
			return ;
		}	

		i = 0;
		while ((*data)->envp[i])
		{
			if (eq && ft_strncmp((*data)->envp[i], env, ft_strlen(env)) == 0 && (*data)->envp[i][ft_strlen(env)] == '=')
			{
				free((*data)->envp[i]);
				(*data)->envp[i] = ft_strdup(cd[j]);
				break;
			}
			else if (!eq && ft_strncmp((*data)->envp[i], env, ft_strlen(env)) == 0 && (*data)->envp[i][ft_strlen(env)] == '=')
			{
				break;
			}
			i++;
		}
		if (!(*data)->envp[i])
		{
			cnt = i;
			new_envp = malloc((cnt + 2) * sizeof(char *));
			if (new_envp == NULL)
			{
				perror("malloc");
				free_split(cd);
				if (eq)
					free(env);
				return ;
			}
			i = 0;
			while (i < cnt)
			{
				new_envp[i] = ft_strdup((*data)->envp[i]);
				i++;
			}
			if (eq)
				new_envp[cnt] = ft_strdup(cd[j]);
			else
				new_envp[cnt] = ft_strjoin(cd[j], "=");
			new_envp[cnt + 1] = NULL;
			free_envp((*data)->envp);
			(*data)->envp = new_envp;
		}
		if (eq)
			free(env);
		j++;
	}
	free_split(cd);
}