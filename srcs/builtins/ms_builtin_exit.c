/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:33:16 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 17:41:58 by kjung            ###   ########.fr       */
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
		exit(0);
	else if (!check_digit(node->args[0]))
	{
		printf("exit: %s: numeric argument required\n", node->args[0]);
		exit(2);
	}
	else if (node->args[1] != NULL)
	{
		printf("too many arguments");
		return ;
	}
	exit((unsigned char)ft_atoi(node->args[0]));
}
