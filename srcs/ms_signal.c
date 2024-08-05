/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:39:57 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/05 09:39:58 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_ctrl(int sig)
{
	g_signal_received = sig;
	if (sig == SIGINT)
	{
		printf("CTRL+C\n");
		ft_prompt();
	}
	else if (sig == SIGTSTP)
    {
        printf("CTRL+Z \n");
        exit(EXIT_FAILURE);
    }
		
}

void	ft_ctrl_signal(void)
{
	struct sigaction set;

	set.sa_handler = sig_ctrl;
	if (sigemptyset(&set.sa_mask) == -1)
		ft_error("SigEmptySet Error");
	set.sa_flags = SA_RESTART; 
    if (sigaction(SIGINT, &set, NULL) == -1)
        ft_error("SigAction Error");
    if (sigaction(SIGTSTP, &set, NULL) == -1)
        ft_error("SigAction Error");
}
