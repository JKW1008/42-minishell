/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:39:57 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/11 17:18:30 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_signal_received;

void sig_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;  // SIGINT 받음
		printf("\n");  // 새 줄
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal_received = 2;  // SIGQUIT 받음
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrl_signal(void)
{
	struct sigaction		sa;
	//int					rc;
	// struct termios		term;
	//set_termios(&term);
	
	signal(SIGQUIT, SIG_IGN); 
	sa.sa_handler = sig_ctrl;
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_error("SigEmptySet Error");
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, 0) == -1)
		ft_error("SigAction Error");
	//if (sigaction(SIGQUIT, &sa, NULL) == -1)
	//	ft_error("SigAction Error");
}
