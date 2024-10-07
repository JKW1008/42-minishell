/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:38:09 by kjung             #+#    #+#             */
/*   Updated: 2024/10/07 16:58:56 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_cnt(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0 && \
		envp[i][ft_strlen(name) == '='])
			return (i);
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
		printf("unset: '%s': not a valid identifier\n", arg);
}

void	do_unset(t_cmd *node, t_data **data)
{
	char	**divided;
	int		i;

	divided = ft_split(node->prompt, ' ');
	if (!divided || !divided[1])
	{
		print_error_and_free(divided, "unset: not enough argumenst");
		return ;
	}
	i = 1;
	while (divided[i])
	{
		unset_arg(data, divided[i]);
		i++;
	}
	free_split(divided);
}
