/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/07/31 13:08:54 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

int	main(void)
{
	t_data	*data;
	
	ft_initalise(&data);
	ft_ctrl_signal();
	ft_prompt();
	//ree(data);
	return (EXIT_SUCCESS);
}
