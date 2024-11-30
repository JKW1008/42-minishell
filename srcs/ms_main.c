/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/30 16:10:56 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received;

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 1 && !*av)
		return (-1);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	ft_initalise(&data, envp);
	ft_ctrl_signal();
	ft_prompt(&data);
	free_envp(data->envp);
	free(data);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
