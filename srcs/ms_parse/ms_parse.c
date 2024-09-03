/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/09/02 15:53:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 

size_t	ft_parser(t_data **data)
{
	if (ft_lexer(data))
		return (-1);
	ms_execute(data);
	return (ft_strlen((*data)->prompt)); // temporary return for -Wall -Werror -Wextra
}
