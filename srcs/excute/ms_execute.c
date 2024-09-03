/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:38:00 by kjung             #+#    #+#             */
/*   Updated: 2024/09/03 14:41:13 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_execute(t_data **data)
{
	printf("%s\n", (*data)->current_path);
	if ((*data)->prompt[0] == 'c' && (*data)->prompt[1] == 'd' && ((*data)->prompt[2] == ' ' && (*data)->prompt[3] == '\0'))
	{
		cd_cmd(data);
	}
	else if (ft_strncmp((*data)->prompt, "pwd", 4))
	{
		char	*tmp;
		tmp = getcwd(NULL, BUFSIZ);
		printf("%s\n", tmp);
		free(tmp);
	}
}

//void	execute_cd(t_data **data)
//{
//	return ;
//}