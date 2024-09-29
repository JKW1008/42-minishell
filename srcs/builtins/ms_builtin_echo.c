/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:41:14 by kjung             #+#    #+#             */
/*   Updated: 2024/09/29 23:44:08 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_charjoin(char *s, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*expand_env(char *arg, t_data **data)
{
	char	*result;
	char	*tmp;
	int		i;
	int		j;
	char	*var_name;
	char	*value;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			j = i + 1;
			while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
				j++;
			var_name = ft_substr(arg, i + 1, j - i - 1);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			value = get_env((*data)->envp, var_name);
			if (value)
				tmp = ft_strjoin(result, value);
			else
				tmp = ft_strdup(result);
			free(var_name);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			free(result);
			result = tmp;
			i = j - 1;
		}
		else
		{
			tmp = ft_charjoin(result, arg[i]);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			free(result);
			result = tmp;
		}
		i++;
	}
	return (result);
}

void	do_echo(t_data **data)
{
	char	**divided;
	char	*expand;
	int		i;
	int		check_n;

	divided = ft_split((*data)->prompt, ' ');
	i = 1;
	check_n = 1;
	if (!divided)
		return ;
	if (divided[1] && ft_strncmp(divided[1], "-n", 2) == 0)
	{
		check_n = 0;
		i = 2;
	}
	while (divided[i])
	{
		expand = expand_env(divided[i], data);
		ft_putstr_fd(expand, 1);
		if (divided[i + 1])
			ft_putchar_fd(' ', 1);
		free(expand);
		i++;
	}
	if (check_n)
		ft_putchar_fd('\n', 1);
	free_split(divided);
}
