/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:33:16 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:33:51 by kjung            ###   ########.fr       */
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

void	do_exit(char *prompt)
{
	char **tmp;

	tmp = ft_split(prompt, ' ');
	printf("exit\n");
	if (tmp[1] == NULL)
		exit(0);
	else if (!check_digit(tmp[1]))
	{
		printf("tmp = %d\n", ft_atoi(tmp[1]));
		printf("numeric argument required");
		exit(2) ;
	}
	else if (tmp[2] != NULL)
	{
		printf("too many arguments");
		return ;
	}
	exit((unsigned char)ft_atoi(tmp[1]));
}