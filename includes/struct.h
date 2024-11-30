/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:45:35 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:34:44 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define MAX_HEREDOCS 100
# include "enum.h"

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
}	t_rdr;	

typedef struct s_cmd
{
	int					ord;
	char				*cmd;
	pid_t				pid_;
	int					is_heredoc;
	int					is_builtin;
	char				**args;
	int					arg_cnt;
	t_rdr				**rdr;
	int					rdr_cnt;
	char				*prompt;
	struct s_data		**data;
	struct s_cmd		*next;
	struct s_cmdline	*cmdline;
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
}	t_token;

typedef struct s_tkn_stk
{
	t_token	*head;
	int		len;
}	t_tkn_stk;

typedef struct s_data
{
	int			errno_;
	char		**envp;
	char		**av;
	char		*prompt;
	t_tkn_stk	*tkn;
	t_cmdline	*cmdline;
}	t_data;

typedef struct s_heredoc
{
	char	*content;
	char	*delimiter;
}	t_heredoc;

typedef struct s_heredoc_list
{
	t_heredoc	heredocs[MAX_HEREDOCS];
	int			count;
}	t_heredoc_list;

typedef struct s_pipe_info
{
	int				pipe_fd[2];
	int				prev_pipe;
	t_heredoc_list	*heredoc_list;
	t_data			**data;
	int				stdin_backup;
	int				stdout_backup;
}	t_pipe_info;

#endif
