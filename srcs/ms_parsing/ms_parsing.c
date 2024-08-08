/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:22:47 by kjung             #+#    #+#             */
/*   Updated: 2024/08/08 15:23:13 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_parser(char *prompt)
{
	ft_lexer(prompt);
	return (ft_strlen(prompt)); // temporary return for -Wall -Werror -Wextra
}
