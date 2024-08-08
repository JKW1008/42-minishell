/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/06 20:56:25 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

int	main(void)
{
	t_data	*data;
	size_t	i;
	
	ft_initalise(&data);
	ft_ctrl_signal();
	ft_prompt();
	//free(data);
	return (EXIT_SUCCESS);
}
