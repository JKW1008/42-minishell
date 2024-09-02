/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_excute_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:59:41 by kjung             #+#    #+#             */
/*   Updated: 2024/09/02 16:30:24 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_home_path(char **envp)
{
	int		i;
	
	i = 0;
	while (ft_strnstr(envp[i], "HOME=", 5) == NULL)
		i++;
	return (envp[i]);
}

void	cd_cmd(t_data **data)
{
	char	*tmp;
	char	**cd;
	char	**path;
	int		i;

	tmp = getcwd(NULL, BUFSIZ);
	if (tmp == NULL)
	{
		perror("getcwd");
		return;
    }
	cd = ft_split((*data)->prompt, ' ');
	if (cd[1] == NULL)
	{
		free(tmp);
		tmp = ft_strdup(find_home_path((*data)->envp));
	}
	else if (cd[2] != NULL)
		printf("minishell: cd: too many arguments\n");
	else
	{
		if (!ft_strncmp(cd[1], "/", 1))
		{
			free(tmp);
			tmp = ft_strdup("/");
		}
		i = 0;
		path = ft_split(cd[1], '/');
		while (path[i])
		{
			if (i == 0 && !ft_strncmp(path[i], "~", 4))
			{
				free(tmp);
				tmp = ft_strdup(find_home_path((*data)->envp));
			}
			else
			{
				if (!ft_strncmp(path[i], "..", 5))
				{
					if (ft_strchr(tmp, '/') == tmp)
						*(ft_strchr(tmp, '/') + 1) = '\0';
					else
						*(ft_strchr(tmp, '/')) = '\0';
				}
				else
				{
					tmp = ft_strjoin(tmp, "/");
					tmp = ft_strjoin(tmp, path[i]);
				}
			}
			i++;
		}
	}
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cd[1]);
	else
	{
		free(tmp);
		tmp = getcwd(NULL, BUFSIZ);
		printf("minishell: %s\n", tmp);
	}
	free_split(cd);
}
