/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:11:47 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 03:01:50 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//	ms_char_handle.c
int			ft_isalnumline(int c);
int			ms_ft_isspace(int c);
int			ft_is_metachar(char c);
t_quote_tbl	ft_quote(char *str);
char		*ft_charjoin(char *s, char c);

//	ms_echo_utils.c
char		*init_result(void);
int			is_valid_var_start(char c);
int			is_valid_var_char(char c);

//	ms_evnp_utils.c
char		*get_env(char **envp, char *name);
char		*get_var_name(char *arg, int start, int *end);
char		*join_value(char *result, char *value);

//	ms_err_uitls.c
void		ft_error(char *msg);
size_t		ft_print_ret(char *msg, int value);

//	ms_excute_utils.c
char		*find_home_path(char **envp);
char		*find_dir(char *path);
void		free_envp(char **envp);
void		env_command(t_data **data);

//	ms_find_path.c
char		*check_absolute_or_home_path(char *str);
char		*check_access(char *split, char *str);
char		*fp_while(char **divided, char *str);
char		*find_path(char **envp, char *str);

//	ms_free_utils.c
int			ft_split_free(char ***sp);
void		free_split(char **str);
void		print_and_free(char **cd, char **envp);
void		print_error_and_free(char **divided, const char *message);

//	ms_token_list_utils.c
int			ft_process_special_chars(char *prompt, int *i, t_tkn_stk **tkns);
int			ft_process_word(char *prompt, int *i, int len, t_tkn_stk **tkns);
void		ft_tokenize_of_while(char *prompt, int len, t_tkn_stk **tkns);

//	ms_tokens_utils.c
int			ft_valid_quotes(char *prompt);
int			ft_token_metachar(char *prompt, t_tkn_stk **tkns);
int			ft_token_quote(char *prompt, t_tkn_stk **tkns, char quote);
t_tkn_stk	*ft_free_tokens(t_tkn_stk *tokens);

#endif