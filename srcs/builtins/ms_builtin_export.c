/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:34:52 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:43:07 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_existing_env(char **envp, char *env, char *cd_j, char *eq)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_strlen(env);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, env_len) == 0 && envp[i][env_len] == '=')
		{
			if (eq)
			{
				free(envp[i]);
				envp[i] = ft_strdup(cd_j);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_new_envp_while(char **new_envp, char **old_envp, int *i, int cnt)
{
	while (*i < cnt)
	{
		new_envp[*i] = ft_strdup(old_envp[*i]);
		if (!new_envp[*i])
		{
			while (--(*i) >= 0)
				free(new_envp[*i]);
			free(new_envp);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

char	**create_new_envp(char **old_envp, char *cd_j, char *eq, int cnt)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc((cnt + 2) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (!create_new_envp_while(new_envp, old_envp, &i, cnt))
		return (NULL);
	if (!eq)
		new_envp[cnt] = ft_strjoin(cd_j, "=");
	else
		new_envp[cnt] = ft_strdup(cd_j);
	if (!new_envp)
	{
		while (--i >= 0)
			free(new_envp[i]);
		free(new_envp);
		return (NULL);
	}
	new_envp[cnt + 1] = NULL;
	return (new_envp);
}

void	process_env_variable(t_data **data, char *cd_j)
{
	char	*eq;
	char	*env;
	char	**new_envp;
	int		cnt;

	eq = ft_strchr(cd_j, '=');
	if (!validate_env_name(cd_j, &env, eq))
		return ;
	if (!update_existing_env((*data)->envp, env, cd_j, eq))
	{
		cnt = 0;
		while ((*data)->envp[cnt])
			cnt++;
		new_envp = create_new_envp((*data)->envp, cd_j, eq, cnt);
		if (new_envp)
		{
			free_envp((*data)->envp);
			(*data)->envp = new_envp;
		}
	}
	if (eq)
		free(env);
}

void	export(t_cmd *node, t_data **data)
{
	int	i;

	i = 0;
	if (!node->args || !node->args[0])
	{
		print_export_env((*data)->envp);
		return ;
	}
	while (i < node->arg_cnt)
	{
		if (node->args[i])
			process_env_variable(data, node->args[i]);
		i++;
	}
}
