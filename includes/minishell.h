/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/10/17 00:45:27 by kjung            ###   ########.fr       */
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

//	ms_cmd.c
void	handle_child_process(t_cmd *cmd, t_pipe_info *info);
void	handle_parent_process(t_cmd *cmd, t_pipe_info *info);
int	is_special_builtin(t_cmd *cmd);
void	process_command(t_cmd *cmd, t_pipe_info *info);
void	execute_pipeline(t_data **data, t_heredoc_list *heredoc_list);


//	ms_execute.c
int		ms_execute(t_cmd *node, t_data **data, int in_child);

//	ms_here_doc.c
char	*get_input(char *prompt);
char	*set_heredoc(t_cmd *node);
void	process_commands(t_data **data, t_heredoc_list *heredoc_list);

//	ms_init.c
char	**copy_envp(char **envp);
t_data	*ft_initalise(t_data **data, char **envp);

//	ms_prompt.c
void	ft_prompt(t_data **data);

//	ms_signal.c
void	ft_ctrl_signal(void);

#endif
