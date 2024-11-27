/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_rdr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:06:46 by kjung             #+#    #+#             */
/*   Updated: 2024/11/26 20:47:39 by kjung            ###   ########.fr       */
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

void	handle_redirections(t_cmd *cmd)
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
		{
			if (cmd->rdr[i]->fd != -1)
			{
				dup2(cmd->rdr[i]->fd, STDIN_FILENO);
				close(cmd->rdr[i]->fd);
			}
		}
		i++;
	}
}
