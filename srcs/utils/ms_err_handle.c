/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:12:28 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/04 17:12:38 by jaehukim         ###   ########.fr       */
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
