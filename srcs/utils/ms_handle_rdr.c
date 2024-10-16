/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_rdr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:06:46 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 23:16:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_rd_in(t_rdr *rdr)
{
	int	fd;

	fd = open(rdr->file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_rd_out(t_rdr *rdr)
{
	int	fd;

	fd = open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_rd_append(t_rdr *rdr)
{
	int	fd;

	fd = open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc(t_rdr *rdr, t_heredoc_list *heredoc_list)
{
	int			j;
	int			pipefd[2];
	t_heredoc	*current_heredoc;

	j = 0;
	while (j < heredoc_list->count)
	{
		current_heredoc = &(heredoc_list->heredocs[j]);
		if (strcmp(rdr->file, current_heredoc->delimiter) == 0)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			write(pipefd[1], current_heredoc->content, \
			strlen(current_heredoc->content));
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			break ;
		}
		j++;
	}
}

void	handle_redirections(t_cmd *cmd, t_heredoc_list *heredoc_list)
{
	int	i;

	i = 0;
	while (i < cmd->rdr_cnt)
	{
		if (cmd->rdr[i]->type == RD_IN)
			handle_rd_in(cmd->rdr[i]);
		else if (cmd->rdr[i]->type == RD_OUT)
			handle_rd_out(cmd->rdr[i]);
		else if (cmd->rdr[i]->type == RD_APPEND)
			handle_rd_append(cmd->rdr[i]);
		else if (cmd->rdr[i]->type == RD_HEREDOC)
			handle_heredoc(cmd->rdr[i], heredoc_list);
		i++;
	}
}
