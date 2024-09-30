/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/30 07:59:12 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

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
