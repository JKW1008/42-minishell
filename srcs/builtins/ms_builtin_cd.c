/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:08:19 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 15:09:56 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_oldpwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			return (envp[i] + 7);
		i++;
	}
	return (NULL);
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
		ft_putstr_fd("too many arguments", 2);
		ft_global_err(1, 1);
		exit(1);
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

int	check_cd_arg(char **tmp, char **cd, char *home, char **envp)
{
	int		result;
	char	*oldpwd;

	if (cd[0] && ft_strncmp(cd[0], "-", 1) == 0)
	{
		oldpwd = get_oldpwd(envp);
		if (oldpwd && *oldpwd)
		{
			*tmp = ft_strdup(oldpwd);
			return (0);
		}
		else
		{
			printf("minishell: cd: OLDPWD not set\n");
			ft_global_err(1, 1);
			return (1);
		}
	}
	result = check_cd_args(cd, tmp, home);
	if (result != 2)
		return (result);
	return (construct_cd_path(cd, tmp, home));
}

void	cd_cmd(t_cmd *node, t_data **data)
{
	char	*tmp;
	char	*home;

	home = find_home_path((*data)->envp);
	if (check_cd_arg(&tmp, node->args, home, (*data)->envp))
	{
		free(home);
		return ;
	}
	if (chdir(tmp) == -1)
	{
		perror("No such file or directory");
		ft_global_err(1, 1);
	}
	else
		envp_update((*data)->envp);
	free(tmp);
	free(home);
}
