/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:39:57 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/21 18:14:33 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	test123(int sig)
{
	sig = sig;
	return;
}

void	default_signal(void)
{
	struct termios  a;


	tcgetattr(0, &a);
	a.c_lflag &= ~(512);
	tcsetattr(0 ,TCSANOW, &a);
	signal(SIGINT, test123);
	signal(SIGQUIT, test123);
	//signal(SIGTSTP, test123);
	return ;
}

void	stop_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return ;
}

void	sig_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal_received = SIGQUIT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTSTP)
	{
		g_signal_received = SIGTSTP;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\nsuspended\n");
		exit(0);
	}
}

//void	ft_ctrl_signal(void)
//{
//	struct sigaction		sa;
//	sa.sa_handler = sig_ctrl;
//	if (sigemptyset(&sa.sa_mask) == -1)
//		ft_error("SigEmptySet Error");
//	sa.sa_flags = SA_RESTART;
//	if (sigaction(SIGINT, &sa, 0) == -1)
//		ft_error("SigAction Error");
//	sa.sa_handler = sig_ctrl;
//	signal(SIGINT, sig_ctrl);
//    signal(SIGQUIT, sig_ctrl);
//    signal(SIGTSTP, sig_ctrl);
//	//if (sigaction(SIGQUIT, &sa, NULL) == -1)
//	//	ft_error("SigAction Error");
//}

void	ft_ctrl_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_ctrl;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("SigAction Error");
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
		ft_error("SigAction Error");
}
