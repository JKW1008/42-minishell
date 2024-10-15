/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:30:52 by kjung             #+#    #+#             */
/*   Updated: 2024/10/15 21:26:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_dir(void)
{
	char	*tmp;

	tmp = getcwd(NULL, BUFSIZ);
	printf("%s\n", tmp);
	free(tmp);
}
