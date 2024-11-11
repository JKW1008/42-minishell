/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:59:27 by jaehukim          #+#    #+#             */
/*   Updated: 2024/03/05 15:17:48 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		else
			s++;
	}
	return (NULL);
}

char	*ft_strchr2(const char *s, int c, int options)
{
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (options == 0)
				return (ft_strdup(s));
		}
		else
			s++;
	}
	return (NULL);
}
