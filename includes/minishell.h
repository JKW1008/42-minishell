/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 03:03:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <sys/signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "parse.h"
# include "builtins.h"
# include "utils.h"
# include "../libft/libft.h"

//	ms_execute.c
void	ms_execute(t_cmd *node, t_data **data);

//	ms_init.c
char	**copy_envp(char **envp);
t_data	*ft_initalise(t_data **data, char **envp);

//	ms_prompt.c
void	ft_prompt(t_data **data);

//	ms_signal.c
void	ft_ctrl_signal(void);

#endif
