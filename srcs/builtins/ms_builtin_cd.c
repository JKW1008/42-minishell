/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:08:19 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:09:22 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cd_args(char **cd, char **tmp, char *home)
{
	if (cd[1] == NULL || !ft_strncmp(cd[1], "~", 2))
	{
		*tmp = ft_strdup(home);
		return (0);
	}
	else if (cd[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (2);
}

int	construct_cd_path(char **cd, char **tmp, char *home)
{
	char	*temp;
	char	cwd[PATH_MAX];

	if (cd[1][0] == '~')
		*tmp = ft_strjoin(home, cd[1] + 1);
	else if (cd[1][0] == '/')
		*tmp = ft_strdup(cd[1]);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return (1);
		}
		temp = ft_strjoin(cwd, "/");
		if (!temp)
			return (1);
		*tmp = ft_strjoin(temp, cd[1]);
		free(temp);
	}
	if (!*tmp)
		return (1);
	return (0);
}

int	check_cd_arg(char **tmp, char **cd, char *home)
{
	int	result;
	
	result = check_cd_args(cd, tmp, home);
	if (result != 2)
		return (result);
	return (construct_cd_path(cd, tmp, home));
}

void	cd_cmd(t_data **data)
{
	char	*tmp;
	char	**cd;
	char	cwd[PATH_MAX];
	char	*home;

	cd = ft_split((*data)->prompt, ' ');
	home = find_home_path((*data)->envp);
	if (check_cd_arg(&tmp, cd, home))
	{
		free_split(cd);
		free(home);
		return ;
	}
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cd[1]);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	free(tmp);
	free_split(cd);
	free(home);
}
