/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:30:52 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 17:40:17 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_dir(void)
{
	char	*tmp;

	tmp = getcwd(NULL, BUFSIZ);
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}
