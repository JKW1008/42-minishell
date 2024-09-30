/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:58:38 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 02:58:59 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_lr_action // LR parser actions
{
	lr_shift,
	lr_remove,
	lr_accept,
	lr_error
}		t_lr_action;

typedef enum e_quote_tbl
{
	normal,
	in_single,
	in_double,
	mixte
}		t_quote_tbl;

typedef enum e_lex_tbl
{
	l_word,
	l_quot_dbl,
	l_quot_sgl,
	l_pipe,
	l_less,
	l_greater,
	l_dbl_less,
	l_dbl_greater,
	l_bck_tick,
	l_bck_slash,
	l_semicolon,
	l_space,
	l_comment,
	l_ampersand,
	l_popen,
	l_pclose,
	l_eof
}		t_lex_tbl;

typedef enum e_token_type
{
	TOKEN_BUILTIN,
	TOKEN_COMMAND,
	TOKEN_REDIRECTION,
	TOKEN_PIPE,
	TOKEN_ARGUMENT
}		t_token_type;

typedef enum e_redir_type
{
	RD_IN,
	RD_OUT,
	RD_APPEND,
	RD_HEREDOC,
	RD_EOF,
}		t_redir_type;

#endif