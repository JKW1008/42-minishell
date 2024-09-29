/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:12:28 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/30 03:02:56 by kjung            ###   ########.fr       */
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
	printf("%s", msg);
	return (value);
}
