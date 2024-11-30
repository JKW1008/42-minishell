/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:33:16 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:42:12 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	handle_overflow(int sign)
{
	if (sign > 0)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

static int	check_overflow(long long num, char c, int sign)
{
	if ((num > LLONG_MAX / 10) || (num == LLONG_MAX / 10 && \
	(c - '0') > LLONG_MAX % 10))
		return (1);
	if ((sign == -1 && (num > LLONG_MAX / 10)) || \
	(num == LLONG_MAX / 10 && (c - '0') > -(LLONG_MIN % 10)))
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(result, str[i], sign))
			return (handle_overflow(sign));
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_digit(char *str)
{
	int			i;
	char		*num_str;
	int			result;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	num_str = ft_lltoa(ft_atoll(str));
	if (!num_str)
		return (0);
	if (str[0] == '+')
		str++;
	result = ft_strncmp(str, num_str, ft_strlen(str));
	free(num_str);
	if (result != 0)
		return (0);
	return (1);
}

void	do_exit(t_cmd *node)
{
	long long	num;

	if (node->args[0] == NULL)
		exit(ft_global_err(0, 2));
	if (!node->args[1])
	{
		if (!check_digit(node->args[0]))
		{
			ft_putstr_fd("numeric argument require\n", 2);
			exit(2);
		}
		else
		{
			num = ft_atoll(node->args[0]);
			ft_global_err((int)num, 1);
			exit((unsigned char)num);
		}
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		ft_global_err(1, 1);
		return ;
	}
}
