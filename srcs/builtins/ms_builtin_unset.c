/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:38:09 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:43:16 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_cnt(char **envp, char *name)
{
	int		i;
	int		name_len;
	char	*eq_pos;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0)
		{
			eq_pos = ft_strchr(envp[i], '=');
			if (eq_pos && eq_pos - envp[i] == name_len)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	remove_env(char **envp, int i)
{
	int	k;

	free(envp[i]);
	k = i;
	while (envp[k])
	{
		envp[k] = envp[k + 1];
		k++;
	}
}

void	unset_arg(t_data **data, char *arg)
{
	int	cnt;

	if (is_env_name(arg))
	{
		cnt = env_cnt((*data)->envp, arg);
		if (cnt != -1)
			remove_env((*data)->envp, cnt);
	}
	else
		return ;
}

void	do_unset(t_cmd *node, t_data **data)
{
	int		i;

	if (!node->args || !node->args[0])
		return ;
	i = 0;
	while (node->args[i])
	{
		unset_arg(data, node->args[i]);
		i++;
	}
}
