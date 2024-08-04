/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:08:52 by jaehukim          #+#    #+#             */
/*   Updated: 2024/07/31 13:08:54 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data *data;

	ft_initalise(&data);
	printf("%s\n", (data)->current_path);
	ft_prompt();

	exit(EXIT_SUCCESS);
}