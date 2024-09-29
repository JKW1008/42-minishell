/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:40:34 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 01:46:44 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_result(void)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (result);
}

int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
