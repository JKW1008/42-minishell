/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/08/11 00:27:48 by kjung            ###   ########.fr       */
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
int		ft_is_metachar(char c);
int		ft_isspace(int c);
t_tkn_stk	*ft_tokenize(char *prompt);

void	free_split(char **str);
char	*check_access(char *split, char *str);
char	*fp_while(char **divided, char *str);
char	*find_path(char **envp, char *str);

void	ft_identify_token_type(t_token *token, char **envp);

#endif

