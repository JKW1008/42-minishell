/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:14:54 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/07 17:26:10 by kjung            ###   ########.fr       */
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
	// l_bck_tick,		// `
	// l_bck_slash,	// "\"
	// l_semicolon,	// ;
	l_space,		// space, tab, newline
	// l_comment,		// #
	// l_ampersand,	// & --> Bonus
	// l_popen,		// ( --> Bonus
	// l_pclose,		// ) --> Bonus
	l_eof			// End of File
}	t_lex_tbl;

typedef	enum e_prs_tbl	// Parsing Table
{
	command,
	simple_cmd,
	cmd_name,
	cmd_word,
	cmd_prefix,
	cmd_suffix,
	io_rdr,
	io_file,
	filename,
	io_here,
	here_end
}	t_prs_tbl;

typedef	struct s_tokens
{
	int				tkn_idx;	// token_idx
	t_lex_tbl 		token_type;	// Parsing Table Value
	char 			*value;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_tkn_stk
{
	t_tokens	*head;
	t_tokens	*tail;
	int		__len__;
}	t_tkn_stk;

# endif