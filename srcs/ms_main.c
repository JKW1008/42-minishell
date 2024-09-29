/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/29 17:26:30 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

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
		printf("%s\n", new_envp[i]);
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

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 1 && !*av)
		return (-1);
	ft_initalise(&data, envp);
	ft_ctrl_signal();
	ft_prompt(&data);
	free_envp(data->envp);
	free_split(data->envp);
	free(data->current_path);
	free(data);
	return (EXIT_SUCCESS);
}
