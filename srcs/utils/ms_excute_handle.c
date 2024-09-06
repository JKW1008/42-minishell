/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_excute_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:59:41 by kjung             #+#    #+#             */
/*   Updated: 2024/09/06 17:20:36 by kjung            ###   ########.fr       */
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


void	cd_cmd(t_data **data)
{
	char	*tmp;
	char	**cd;
	char	cwd[PATH_MAX];
	char	*home;

	cd = ft_split((*data)->prompt, ' ');
	home = find_home_path((*data)->envp);
	printf("%s\n", home);
	if (cd[1] == NULL || !ft_strncmp(cd[1], "~", 2))
		tmp = ft_strdup(home);
	else if (cd[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		free_split(cd);
		free(home);
		return ;
	}
	else
	{
		if (cd[1][0] == '~')
			tmp = ft_strjoin(home, cd[1] + 1);
		else if (cd[1][0] == '/')
			tmp = ft_strdup(cd[1]);
		else
		{
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("getcwd");
				free_split(cd);
				free(home);
				return ;
			}
			tmp = ft_strjoin(cwd, "/");
			tmp = ft_strjoin(tmp, cd[1]);
		}
	}
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cd[1]);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	free(tmp);
	free_split(cd);
}

void	printenv(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])	
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(char *prompt)
{
	char **tmp;

	tmp = ft_split(prompt, ' ');
	printf("exit\n");
	if (tmp[1] == NULL)
		exit(0);
	else if (!check_digit(tmp[1]))
	{
		printf("tmp = %d\n", ft_atoi(tmp[1]));
		printf("numeric argument required");
		exit(2) ;
	}
	else if (tmp[2] != NULL)
	{
		printf("too many arguments");
		return ;
	}
	exit((unsigned char)ft_atoi(tmp[1]));
}

