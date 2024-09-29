/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:11:26 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 01:57:20 by kjung            ###   ########.fr       */
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

int	validate_env_name(char *cd, char **env, char *eq)
{
	if (!eq)
		*env = cd;
	else
		*env = ft_substr(cd, 0, eq - cd);
	if (!is_env_name(*env))
	{
		printf("Invalid environment variable name: %s\n", cd);
		if (eq)
			free(*env);
		return (0);
	}
	return (1);
}

int	check_eqaul(char *env)
{
	if (ft_strchr(env, '=') != NULL)
		return (1);
	else
		return (0);
}

void	printenv(char **envp, int flag)
{
	while (*envp != NULL)
	{
		if (flag == 1)
		{
			if (check_eqaul(*envp) == 1)
			{
				ft_putstr_fd("declare -x ", 1);
				write(1, *envp, ft_strchr(*envp, '=') - *envp);
				write(1, "=\"", 2);
				ft_putstr_fd(ft_strchr(*envp, '=') + 1, 1);
				write(1, "\"\n", 2);
			}
			else if (check_eqaul(*envp) == 0)
				printf("declare -x %s\n", *envp);
		}
		else
		{
			if (check_eqaul(*envp) == 1)
				printf("%s\n", *envp);
		}
		envp++;
	}
}
