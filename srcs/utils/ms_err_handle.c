/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:12:28 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/30 15:19:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *msg)
{
	if (msg)
		perror(msg);
	else
		perror(NULL);
	exit(EXIT_FAILURE);
}

size_t	ft_print_ret(char *msg, int value)
{
	ft_putstr_fd(msg, 2);
	return (value);
}

size_t	ft_global_err(int i, int type)
{
	static size_t	now_err;
	static size_t	old_err;

	if (type == 0)
		;
	else if (type == 1)
		now_err = i;
	else if (type == 2)
		return (old_err);
	else if (type == 3)
	{
		old_err = now_err;
		now_err = 0;
	}
	return (now_err);
}
