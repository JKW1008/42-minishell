/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:54:53 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/11 14:54:53 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concate(char **sp, int i, int idx)
{
	int		j;
	int		counter;
	int		total_len;
	char	*ret;

	counter = 0;
	total_len = 0;
	while (sp[counter])
		total_len += ft_strlen(sp[counter++]);
	ret = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!ret)
		return (NULL);
	while (sp[idx])
	{
		j = 0;
		while (sp[idx][j])
		{
			ret[i++] = sp[idx][j++];
		}
		idx++;
	}
	ret[i] = '\0';
	return (ret);
}
