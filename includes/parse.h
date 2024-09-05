/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:14:54 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/20 18:35:23 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

typedef enum e_lr_action // LR parser actions
{
	lr_shift,
	lr_remove,
	lr_accept,
	lr_error
}	t_lr_action;

typedef enum e_quote_tbl
{
	normal,
	in_single,
	in_double
}	t_quote_tbl;

typedef enum e_lex_tbl	// Lexer Table
{
	l_word,			// [0-9a-zA-Z_]+
	l_quot_dbl,		// ""
	l_quot_sgl,		// ''
	l_pipe,			// |
	l_less,			// <
	l_greater,		// >
	l_dbl_less,		// <<
	l_dbl_greater,	// >>
	l_bck_tick,		// `
	l_bck_slash,	// "\"
	l_semicolon,	// ;
	l_space,		// space, tab, newline
	l_comment,		// #
	l_ampersand,	// & --> Bonus
	l_popen,		// ( --> Bonus
	l_pclose,		// ) --> Bonus
	l_eof			// End of File
}	t_lex_tbl;


typedef	struct s_token
{
	int				tkn_idx;	// token_idx
	t_lex_tbl 		token_type;	// Parsing Table Value
	t_quote_tbl		qt_status;
	char 			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_token_type
{
	TOKEN_BUILTIN,
	TOKEN_COMMAND,
	TOKEN_REDIRECTION,
	TOKEN_PIPE,
	TOKEN_ARGUMENT
} t_token_type;

typedef struct s_tkn_stk
{
	t_token	*head;
	int		len;
}	t_tkn_stk;

typedef enum e_redir_type
{
	RD_IN, // <
	RD_OUT, // >
	RD_APPEND, // >>
	RD_HEREDOC, // <
	RD_EOF,
} t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_rdr;	

typedef	struct s_args
{
	char	*og;
	char	*ex;
}	t_args;

typedef	struct s_cmd
{
	char			*cmd;
	int				is_heredoc;
	t_args			**args;
	int				arg_cnt;
	t_rdr			**rdr;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_cmdline
{
	t_cmd	*head;
	int		count;
}	t_cmdline;


# endif