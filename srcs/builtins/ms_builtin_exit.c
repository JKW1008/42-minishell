/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:33:16 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 16:12:37 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(t_cmd *node)
{
	printf("exit\n");
	if (node->args[0] == NULL)
	{
		ft_global_err(0, 1);
		exit(0);
	}	
	if (node->args[1] != NULL)
	{
		ft_putstr_fd("too many arguments", 2);
		exit(1);
	}
	if (!('0' <= node->args[0][0] && node->args[0][0] <= '9') && \
	!('0' <= node->args[0][1] && node->args[0][1] <= '9'))
	{
		ft_putstr_fd("numeric argument required", 2);
		exit(2);
	}
	ft_global_err(ft_atoi(node->args[0]), 1);
	exit((unsigned char)ft_atoi(node->args[0]));
}
