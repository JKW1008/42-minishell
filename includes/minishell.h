/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/07/31 15:01:07 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include "parse.h" 
# include "../libft/libft.h"
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


extern volatile sig_atomic_t g_signal_received = 0;

typedef struct s_data
{
	char	*current_path;

}	t_data;

void	ft_error(char *msg);
t_data *ft_initalise(t_data **data);
void	ft_ctrl_signal(void);
void	ft_prompt(void);
size_t	ft_parser(char *prompt);
size_t	ft_lexer(char *prompt);
int		ft_isalnumline(int c);
int		ft_isspace(int c);

#endif

