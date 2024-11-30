/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:41:04 by kjung             #+#    #+#             */
/*   Updated: 2024/11/30 23:45:03 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_len(long long n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	fill_str(char *str, long long n, int len)
{
	int			start;
	long long	tmp;

	start = 0;
	if (n < 0)
	{
		str[0] = '-';
		start = 1;
	}
	str[len] = '\0';
	while (len-- > start)
	{
		if (n < 0)
			tmp = -(n % 10);
		else
			tmp = n % 10;
		str[len] = tmp + '0';
		n = n / 10;
	}
}

char	*ft_lltoa(long long n)
{
	char	*str;
	int		len;

	len = get_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, n, len);
	return (str);
}
