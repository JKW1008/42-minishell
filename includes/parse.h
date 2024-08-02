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

typedef enum e_lr_action
{
	shift,
	remove,
	accept,
	error,
}	t_lr_action;

typedef enum e_lex_tbl
{
	word,			// [0-9a-zA-Z]+
	quot_dbl,		// ""
	quot_sgl,		// ''
	pipe,			// |
	less,			// <
	greater,		// >
	dbl_greater,	// >>
	bck_tick,		// `
	bck_slash,		// "\"
}	t_lex_tbl;

typedef	enum e_prs_tbl
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
}


#endif