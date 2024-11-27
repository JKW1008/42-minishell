/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:09:22 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/25 21:32:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_data	*ft_initalise(t_data **data, char **envp)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!(*data))
		ft_error(NULL);
	(*data)->prompt = NULL;
	(*data)->envp = copy_envp(envp);
	(*data)->cmdline = NULL;
	(*data)->tkn = NULL;
	return (*data);
}
