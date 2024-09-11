/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:09:22 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/09 20:06:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_initalise(t_data **data, char **envp)
{
	*data = (t_data *) malloc(sizeof(t_data));
	if (!(*data))
		ft_error(NULL);
	(*data)->current_path = (char *) malloc(sizeof(char) * 100);
	if (!(*data)->current_path)
		ft_error(NULL);
	(*data)->current_path = getcwd(NULL, 0);
	(*data)->prompt = NULL;
	(*data)->envp = copy_envp(envp);
	return (*data);
}
