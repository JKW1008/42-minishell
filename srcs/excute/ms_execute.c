/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:38:00 by kjung             #+#    #+#             */
/*   Updated: 2024/09/10 16:14:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_execute(t_data **data)
{
	if ((*data)->prompt[0] == 'c' && (*data)->prompt[1] == 'd' && ((*data)->prompt[2] == ' ' || (*data)->prompt[2] == '\0'))
		cd_cmd(data);
	else if (!ft_strncmp((*data)->prompt, "pwd", 4))
	{
		char	*tmp;
		tmp = getcwd(NULL, BUFSIZ);
		printf("%s\n", tmp);
		free(tmp);
	}
	else if (!ft_strncmp((*data)->prompt, "env", 4))
		env_command(data);
	else if (!ft_strncmp((*data)->prompt, "exit", 5) || !ft_strncmp((*data)->prompt, "exit ", 5))
		do_exit((*data)->prompt);
	else if (!ft_strncmp((*data)->prompt, "export ", 6))
		export(data);
	else if (!ft_strncmp((*data)->prompt, "unset ", 5))
		do_unset(data);
	// else if (!ft_strncmp((*data)->prompt, "ls", 2))
	// {
		
	// }
}

//void	execute_cd(t_data **data)
//{
//	return ;
//}