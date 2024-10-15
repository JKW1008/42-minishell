/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:08:19 by kjung             #+#    #+#             */
/*   Updated: 2024/10/15 21:30:28 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	envp_update(char **envp)
{
	char	pwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	envp_update_while(envp, &old_pwd, pwd);
}

int	check_cd_args(char **args, char **tmp, char *home)
{
	if (args[0] == NULL || !ft_strncmp(args[0], "~", 2))
	{
		*tmp = ft_strdup(home);
		return (0);
	}
	else if (!ft_strncmp(args[0], "..", 2))
	{
		*tmp = ft_strdup("..");
		return (0);
	}
	else if (args[1] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (2);
}

int	construct_cd_path(char **args, char **tmp, char *home)
{
	char	*temp;
	char	cwd[PATH_MAX];

	if (args[0][0] == '~')
		*tmp = ft_strjoin(home, args[1] + 1);
	else if (args[0][0] == '/' || !ft_strncmp(args[0], "..", 2))
		*tmp = ft_strdup(args[1]);
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
		*tmp = ft_strjoin(temp, args[0]);
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

void	cd_cmd(t_cmd *node, t_data **data)
{
	char	*tmp;
	char	cwd[PATH_MAX];
	char	*home;
	
	home = find_home_path((*data)->envp);
	if (check_cd_arg(&tmp, node->args, home))
	{
		free(home);
		return ;
	}
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", node->args[1]);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	envp_update((*data)->envp);
	free(tmp);
	free(home);
}
