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
		printf("\n");
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
	else if (sig == SIGTSTP)
    {
        g_signal_received = 3;// SIGTSTP 받음
		//signal(SIGTSTP, SIG_DFL);
		//raise(SIGTSTP);            // 현재 프로세스에 SIGTSTP 시그널 전송
        //signal(SIGTSTP, sig_ctrl);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\nsuspended\n");
		exit(0) ;
        //signal(SIGTSTP, SIG_DFL);  
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

void ft_ctrl_signal(void)
{
    struct sigaction sa;
    
    sa.sa_handler = sig_ctrl;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    
    if (sigaction(SIGINT, &sa, NULL) == -1)
        ft_error("SigAction Error");
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        ft_error("SigAction Error");
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
        ft_error("SigAction Error");
}
