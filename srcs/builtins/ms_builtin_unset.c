/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:38:09 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:39:04 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_unset(t_data **data)
{
	char	**divided;
	int		i;
	int		j;
	int		k;

	divided = ft_split((*data)->prompt, ' ');
	if (!divided || !divided[1])
	{
		printf("unset: not enough arguments\n");
		free_split(divided);
		return ;
	}
	i = 1;
	while (divided[i])
	{
		if (is_env_name(divided[i]))
		{
			j = 0;
			while ((*data)->envp[i])
			{
				if (ft_strncmp((*data)->envp[j], divided[i], ft_strlen(divided[i])) == 0 && (*data)->envp[j][ft_strlen(divided[i])] == '=')
				{
					free((*data)->envp[j]);
					k = j;
					while ((*data)->envp[k])
					{
						(*data)->envp[k] = (*data)->envp[k + 1];
						k++;
					}
					j--;
					break ;
				}
				j++;
			}
		}
		else
		{
			printf("unset: '%s': not a valid identifier\n", divided[i]);
		}
		i++;
	}
	free_split(divided);
}