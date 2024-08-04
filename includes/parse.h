/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:14:54 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/02 11:14:56 by jaehukim         ###   ########.fr       */
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
	l_word,			// [0-9a-zA-Z]+
	l_quot_dbl,		// ""
	l_quot_sgl,		// ''
	l_pipe,			// |
	l_less,			// <
	l_greater,		// >
	l_dbl_greater,	// >>
	l_bck_tick,		// `
	l_bck_slash,	// "\"
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
# endif