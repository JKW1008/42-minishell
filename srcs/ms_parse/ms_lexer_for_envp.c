/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_for_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:29:25 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/11 11:29:26 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_replace_envp_val(char **str, int i, char **item)
{
	int		dstlen;
	char	*dst;

	dstlen = ft_strlen(*str) + ft_strlen(item[1]) - (ft_strlen(item[0]) + 1);
	dst = (char *) ft_calloc(sizeof(char), (dstlen + 1));
	ft_strlcpy(dst, *str, i + 1);
	ft_strlcpy(dst + i, item[1], ft_strlen(item[1]) + 1);
	ft_strlcpy(dst + i + ft_strlen(item[1]), \
				*str + i + ft_strlen(item[0]) + 1, \
				dstlen - (i + ft_strlen(item[1])) + 1);
	free(*str);
	*str = ft_strdup(dst);
	free(dst);
	return (0);
}

static int	convert_envp_value(char **value, t_data *data)
{
	int		envp_ord;
	char	**item;

	envp_ord = -1;
	while (data->envp[++envp_ord])
	{
		item = ft_split(data->envp[envp_ord], '=');
		if (ft_strncmp(*value + 1, item[0], ft_strlen(*value + 1)) == 0)
		{
			ft_replace_envp_val(value, 0, item);
			return (0);
		}
		free_split(item);
	}
	return (1);
}

static size_t	ft_search_errno(char **str)
{
	char	*err;

	err = ft_itoa(ft_global_err(0, 2));
	free(*str);
	*str = err;
	return (0);
}

size_t	ft_search_envp(char **str, t_data *data)
{
	int		start_idx;
	char	**tmp;

	start_idx = 1;
	if (*str[0] == '$' && ft_strlen(*str) > 1)
	{
		tmp = ft_split2(*str, ' ');
		if (ft_strncmp(tmp[0], "$?", ft_strlen(tmp[0])) == 0)
			start_idx = ft_search_errno(&tmp[0]);
		else
			start_idx = convert_envp_value(&tmp[0], data);
		free(*str);
		*str = ft_concate(tmp, 0, start_idx);
		free_split(tmp);
	}
	return (0);
}
