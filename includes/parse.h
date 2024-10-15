/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:14:54 by jaehukim          #+#    #+#             */
/*   Updated: 2024/10/15 17:31:04 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"
# include <stdlib.h>

//	ms_alloc_rdr.c
int			ft_cmd_rdr(t_cmd *cmd, t_token *tkn);

//	ms_alloc_simplecmd.c
int			ft_alloc_simplecmd(t_cmd *cmd, t_token *tkn);

//	ms_lex_utils.c
int			ft_is_command(const char *token, char **envp);
int			ft_is_builtin(const char *token);
int			ft_is_redirection(const char *token);
int			ft_is_heredoc(char *token);

//	ms_lexer.c
void		ft_set_qt_value(t_token *tkn);
size_t		ft_replace_envp_val(char *str, int i, char **item);
size_t		ft_search_envp(t_token *tkn, int i, t_data *data);
void		ft_set_valex(t_token *tkn, t_data *data);
size_t		ft_lexer(t_data **data);

// ms_merge_tokens.c
size_t	ft_merge_tokens(t_data **data);


//	ms_parse.c
int			ft_init_cmdline(t_data **data);
size_t		ft_parser(t_data **data);

//	ms_tokenize.c
void		ft_init_stk_tokens(t_tkn_stk **tkns);
t_token		*ft_creat_token(char *prompt, int start, int cnt);
void		ft_add_token_for_list(t_token *tok, t_tkn_stk **tkns);
int			ft_add_token(char *prompt, int start, int cnt, t_tkn_stk **tkns);
t_tkn_stk	*ft_tokenize(char *prompt);

//	ms_tokens_type_utils.c
void		ft_identify_token_type2(t_token *token);
void		ft_identify_token_type(t_token *token, char **envp);

// ms_sort_ord.c
size_t		ft_sort_ord(t_data **data);

#endif
