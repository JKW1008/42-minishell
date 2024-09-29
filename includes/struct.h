/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:45:35 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 02:59:09 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "enum.h"

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}	t_rdr;	

typedef struct s_args
{
	char	*og;
	char	*ex;
}		t_args;

typedef struct s_cmd
{
	int				ord;
	char			*cmd;
	int				is_heredoc;
	int				is_builtin;
	char			**args;
	int				arg_cnt;
	t_rdr			**rdr;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_cmdline
{
	t_cmd	*head;
	int		count;
}		t_cmdline;

typedef struct s_token
{
	int				tkn_idx;
	t_lex_tbl		token_type;
	t_quote_tbl		qt_status;
	char			*value;
	char			pre_sep;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_tkn_stk
{
	t_token	*head;
	int		len;
}	t_tkn_stk;

typedef struct s_data
{
	int			errno_;
	char		*current_path;
	char		**envp;
	char		*prompt;
	t_tkn_stk	*tkn;
	t_cmdline	*cmdline;
}	t_data;

#endif
