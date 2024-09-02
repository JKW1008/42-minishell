/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:38:00 by kjung             #+#    #+#             */
/*   Updated: 2024/09/02 16:23:00 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_execute(t_data **data)
{
	if ((*data)->prompt[0] == 'c' && (*data)->prompt[1] == 'd')
	{
		printf("%s\n", (*data)->prompt);
		cd_cmd(data);
	}
}

// void	execute_cd(t_data **data)
// {
	
// }