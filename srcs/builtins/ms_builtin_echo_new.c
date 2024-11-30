/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:45:40 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/30 23:36:48 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_echo_options(char **args, int *i)
{
	int	check_n;
	int	j;

	check_n = 1;
	*i = 0;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			check_n = 0;
			(*i)++;
		}
		else
			break ;
	}
	return (check_n);
}

int	do_echo(t_cmd *node)
{
	int		i;
	int		check_n;
	char	*str;

	check_n = process_echo_options(node->args, &i);
	while (node->args[i])
	{
		str = node->args[i];
		if (str)
		{	
			printf("%s", str);
			if (node->args[i + 1])
				printf(" ");
		}
		i++;
	}
	if (check_n)
		printf("\n");
	return (0);
}
