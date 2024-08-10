/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:13:47 by kjung             #+#    #+#             */
/*   Updated: 2024/08/11 00:13:57 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check_access(char *split, char *str)
{
	char	*filename;
	char	*tmp;

	if (!split || !str)
		return (NULL);
	tmp = ft_strjoin(split, "/");
	if (!tmp)
		return (NULL);
	filename = ft_strjoin(tmp, str);
	free(tmp);
	if (!filename)
		return (NULL);
	if (access(filename, F_OK | X_OK) == 0)
		return (filename);
	else
	{
		free(filename);
		return (NULL);
	}
}

char	*fp_while(char **divided, char *str)
{
	int		i;
	char	*res;
	char	**split;

	i = 0;
	split = ft_split(divided[1], ':');
	while (split[i])
	{
		res = check_access(split[i], str);
		if (res != NULL)
		{
			free_split(split);
			return (res);
		}
		i++;
	}
	res = check_access(".", str);
	if (res != NULL)
	{
		free_split(split);
		return (res);
	}
	free_split(split);
	return (NULL);
}

char	*find_path(char **envp, char *str)
{
	int		i;
	char	**divided;
	char	*res;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	res = check_absolute_or_home_path(str);
	if (res)
		return (res);
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	divided = ft_split(envp[i], '=');
	res = fp_while(divided, str);
	if (res != NULL)
	{
		free_split(divided);
		return (res);
	}
	free_split(divided);
	return (NULL);
}