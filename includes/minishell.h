/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 22:42:11 by kjung            ###   ########.fr       */
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
# include <fcntl.h>
# include "parse.h"
# include "builtins.h"
# include "utils.h"
# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>

extern volatile sig_atomic_t	g_signal_received;

//	ms_cmd.c
void	check_dir(t_cmd *cmd);
void	execute_command(t_cmd *cmd, t_data **data);
int		is_special_builtin(t_cmd *cmd);
void	handle_redirection_only(t_cmd *cmd, t_pipe_info *info);
void	execute_pipeline(t_data **data);

//	ms_execute.c
int		ms_execute(t_cmd *node, t_data **data, int in_child);
int		ms_execute2(t_cmd *node, t_data **data, int in_child);

//	ms_here_doc.c
void	process_heredoc(t_data **data);

//	ms_init.c
char	**copy_envp(char **envp);
t_data	*ft_initalise(t_data **data, char **envp);

//	ms_process.c
void	wait_all_children(t_cmd *cmd);
void	handle_child_process(t_cmd *cmd, t_pipe_info *info);
void	handle_parent_process(t_cmd *cmd, t_pipe_info *info);
void	process_command(t_cmd *cmd, t_pipe_info *info);

//	ms_prompt.c
void	ft_prompt(t_data **data);

//	ms_signal.c
void	default_signal(void);
void	stop_signal(void);
void	ft_ctrl_signal(void);
void	sig_ctrl(int sig);

void	ft_destroy_parser_context(t_data **data);

#endif
