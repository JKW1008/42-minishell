/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_char_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:27:01 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/30 02:12:21 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnumline(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_' || c == '-')
		return (1);
	else
		return (0);
}

int	ms_ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' \
	|| c == '\n' || c == '\f')
		return (1);
	return (0);
}

int	ft_is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '=');
}

t_quote_tbl	ft_quote(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '\'' && str[len - 1] == '\'')
		return (in_single);
	else if (str[0] == '"' && str[len - 1] == '"')
		return (in_double);
	else
		return (normal);
}

char	*ft_charjoin(char *s, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}
