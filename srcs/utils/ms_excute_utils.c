/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_excute_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:59:41 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:46:17 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_home_path(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = envp[i] + 5;
			return (ft_strdup(home));
		}
		i++;
	}
	return (NULL);
}

char	*find_dir(char *path)
{
	char	*last;

	last = ft_strrchr(path, '/');
	if (last == path)
		return (ft_strdup("/"));
	if (last)
		*last = '\0';
	return (ft_strdup(path));
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	env_command(t_data **data)
{
	printenv((*data)->envp, 0);
}
