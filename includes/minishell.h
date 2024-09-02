/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:23:02 by kjung             #+#    #+#             */
/*   Updated: 2024/08/29 16:25:36 by kjung            ###   ########.fr       */
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
	int			errno_;
	char		*current_path;
	char		**envp;
	char		*prompt;
	t_tkn_stk	*tkn;
}	t_data;

void		ft_error(char *msg);
size_t		ft_print_ret(char *msg, int value);
t_data *	ft_initalise(t_data **data, char **envp);
void		ft_ctrl_signal(void);
void		ft_prompt(t_data **data);
size_t		ft_parser(t_data **data);
size_t		ft_lexer(t_data **data);
int			ft_isalnumline(int c);
int			ft_is_metachar(char c);
int			ft_isspace(int c);
t_quote_tbl ft_quote(char *str);
t_tkn_stk	*ft_tokenize(char *prompt);

void		free_split(char **str);
char		*check_access(char *split, char *str);
char		*fp_while(char **divided, char *str);
char		*find_path(char **envp, char *str);

void		ft_identify_token_type(t_token *token, char **envp);
t_tkn_stk	*ft_free_tokens(t_tkn_stk *tokens);

char		*ft_replace_substring(const char *str, const char *start, const char *end, const char *replacement);
size_t		ft_expand_env_vars(t_token *token, char **envp);
size_t		ft_process_env_var(char **expanded, char **start, char **envp);
size_t		ft_validate_token_structure(t_tkn_stk *tokens);

void	ms_execute(t_data **data);

#endif

