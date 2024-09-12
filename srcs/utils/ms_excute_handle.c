/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_excute_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:59:41 by kjung             #+#    #+#             */
/*   Updated: 2024/09/12 16:34:01 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_home_path(char **envp)
{
	int		i;
	char	*home;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = envp[i] + 5;
			return (ft_strdup(home));
		}
		i++;
	}
	return (NULL);
}

char	*find_dir(char *path)
{
	char	*last;
	
	last = ft_strrchr(path, '/');
	if (last == path)
		return (ft_strdup("/"));
	if (last)
		*last = '\0';
	return (ft_strdup(path));
}

void	cd_cmd(t_data **data)
{
	char	*tmp;
	char	**cd;
	char	cwd[PATH_MAX];
	char	*home;

	cd = ft_split((*data)->prompt, ' ');
	home = find_home_path((*data)->envp);
	printf("%s\n", home);
	if (cd[1] == NULL || !ft_strncmp(cd[1], "~", 2))
		tmp = ft_strdup(home);
	else if (cd[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		free_split(cd);
		free(home);
		return ;
	}
	else
	{
		if (cd[1][0] == '~')
			tmp = ft_strjoin(home, cd[1] + 1);
		else if (cd[1][0] == '/')
			tmp = ft_strdup(cd[1]);
		else
		{
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("getcwd");
				free_split(cd);
				free(home);
				return ;
			}
			tmp = ft_strjoin(cwd, "/");
			tmp = ft_strjoin(tmp, cd[1]);
		}
	}
	if (chdir(tmp) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cd[1]);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	free(tmp);
	free_split(cd);
}

int		check_eqaul(char *env)
{
	if (ft_strchr(env, '=') != NULL)
		return (1);
	else
		return (0);
}

void	printenv(char **envp, int flag)
{
	while (*envp != NULL)
	{
		if (flag == 1)
		{
			if (check_eqaul(*envp) == 1)
			{
				ft_putstr_fd("declare -x ", 1);
				write(1, *envp, ft_strchr(*envp, '=') - *envp);
				write(1, "=\"", 2);
				ft_putstr_fd(ft_strchr(*envp, '=') + 1, 1);
				write(1, "\"\n", 2);
			}
			else if (check_eqaul(*envp) == 0)
				printf("declare -x %s\n", *envp);
		}
		else
		{
			if (check_eqaul(*envp) == 1)
				printf("%s\n", *envp);
		}
		envp++;
	}
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(char *prompt)
{
	char **tmp;

	tmp = ft_split(prompt, ' ');
	printf("exit\n");
	if (tmp[1] == NULL)
		exit(0);
	else if (!check_digit(tmp[1]))
	{
		printf("tmp = %d\n", ft_atoi(tmp[1]));
		printf("numeric argument required");
		exit(2) ;
	}
	else if (tmp[2] != NULL)
	{
		printf("too many arguments");
		return ;
	}
	exit((unsigned char)ft_atoi(tmp[1]));
}

int	is_env_name(char *str)
{
   int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export(t_data **data)
{
	char	**cd;
	char	*eq;
	char	*env;
	char	**new_envp;
	int		i;
	int		cnt;

	cd = ft_split((*data)->prompt, ' ');
	if (!cd || !cd[1])
	{
		printenv((*data)->envp, 1);
		free_split(cd);
		return ;
	}
	eq = ft_strchr(cd[1], '=');
	if (eq)
		env = ft_substr(cd[1], 0, eq - cd[1]);
	else
		env = cd[1];
	if (!is_env_name(env))
	{
		printf("Invalid environment variable name: %s\n", cd[1]);
		free_split(cd);
		if (eq)
			free(env);
		return ;
	}	
	i = 0;
	while ((*data)->envp[i])
	{
		if (eq && ft_strncmp((*data)->envp[i], cd[1], eq - cd[1]) == 0 && (*data)->envp[i][eq - cd[1]] == '=')
		{
			free((*data)->envp[i]);
			(*data)->envp[i] = ft_strdup(cd[1]);
			free_split(cd);
			return ;
		}
		else if (!eq && ft_strncmp((*data)->envp[i], cd[1], ft_strlen(cd[1])) == 0 && (*data)->envp[i][ft_strlen(cd[1])] == '=')
		{
			free_split(cd);
			return ;
		}
		i++;
	}
	cnt = i;
	new_envp = malloc((cnt + 2) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		free_split(cd);
		return ;
	}
	i = 0;
	while (i < cnt)
	{
		new_envp[i] = ft_strdup((*data)->envp[i]);
		i++;
	}
	if (eq)
		new_envp[cnt] = ft_strdup(cd[1]);
	else
		new_envp[cnt] = ft_strjoin(cd[1], "=");
	new_envp[cnt + 1] = NULL;
	free_envp((*data)->envp);
	(*data)->envp = new_envp;
	free_split(cd);
}

void free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	env_command(t_data **data)
{
   printenv((*data)->envp, 0);
}

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

char	*ft_charjoin(char *s, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, ft_strlen(s));
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*expand_env(char *arg, t_data **data)
{
	char	*result;
	char	*tmp;
	int		i;
	int		j;
	char	*var_name;
	char	*value;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			j = i + 1;
			while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
				j++;
			var_name = ft_substr(arg, i + 1, j - i - 1);
			value = get_env((*data)->envp, var_name);
			if (value)
				tmp = ft_strjoin(result, value);
			else
				tmp = ft_strjoin(result, "");
			free(result);
			result = tmp;
			free(var_name);
			i = j - 1;
		}
		else
		{
			tmp = ft_charjoin(result, arg[i]);
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

	printf("fuck");
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
