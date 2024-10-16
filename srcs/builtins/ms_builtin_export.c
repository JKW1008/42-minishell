/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:34:52 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 21:19:51 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_existing_env(char **envp, char *env, char *cd_j, char *eq)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (eq && ft_strncmp(envp[i], env, ft_strlen(env)) == 0 && \
		envp[i][ft_strlen(env)] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(cd_j);
			return (1);
		}
		else if (!eq && ft_strncmp(envp[i], env, ft_strlen(env)) == 0 && \
		envp[i][ft_strlen(env)] == '=')
			return (1);
		i++;
	}
	return (0);
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
	while (i < cnt)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	if (!eq)
		new_envp[cnt] = ft_strjoin(cd_j, "=");
	else
		new_envp[cnt] = ft_strdup(cd_j);
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
	int		i;
	char	*full_args;
	char	*temp;

	i = 0;
	if (!node->args || !node->args[0])
	{
		print_and_free((*data)->envp);
		return ;
	}
	while (node->args[i])
	{
		if (i + 2 < node->arg_cnt && ft_strncmp(node->args[i + 1], "=", 1) == 0)
		{
			temp = ft_strjoin(node->args[i], node->args[i + 1]);
			full_args = ft_strjoin(temp, node->args[i + 2]);
			free(temp);
			process_env_variable(data, full_args);
			free(full_args);
			i += 3;
		}
		else
			process_env_variable(data, node->args[i++]);
	}
}
