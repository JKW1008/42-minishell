/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:41:14 by kjung             #+#    #+#             */
/*   Updated: 2024/10/16 17:42:28 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_char(char *result, char c)
{
	char	*tmp;

	tmp = ft_charjoin(result, c);
	free(result);
	return (tmp);
}

char	*expand_env_var(char *arg, int *i, t_data **data, char *result)
{
	int		j;
	char	*var_name;
	char	*value;
	char	*tmp;

	var_name = get_var_name(arg, *i, &j);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	value = get_env((*data)->envp, var_name);
	tmp = join_value(result, value);
	free(var_name);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	*i = j - 1;
	return (tmp);
}

char	*expand_env(char *arg, t_data **data)
{
	char	*result;
	int		i;

	result = init_result();
	if (!result)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && is_valid_var_start(arg[i + 1]))
		{
			result = expand_env_var(arg, &i, data, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = join_char(result, arg[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

int	process_echo_options(char **args, int *i)
{
	int	check_n;

	check_n = 1;
	*i = 0;
	if (args[0] && ft_strncmp(args[0], "-n", 2) == 0)
	{
		check_n = 0;
		*i = 1;
	}
	return (check_n);
}

int	do_echo(t_cmd *node, t_data **data)
{
	char	*expand;
	int		i;
	int		check_n;

	check_n = process_echo_options(node->args, &i);
	while (node->args[i])
	{
		expand = expand_env(node->args[i], data);
		if (expand)
		{
			ft_putstr_fd(expand, 1);
			if (node->args[i + 1])
				ft_putchar_fd(' ', 1);
			free(expand);
		}
		i++;
	}
	if (check_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
