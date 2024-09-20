/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/09/02 16:06:43 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_qt_value(t_token *tkn)
{
	int	len;

	len = ft_strlen(tkn->value);
	ft_memmove(tkn->value, tkn->value + 1, len - 2);
	tkn->value[len - 2] = 0;
	tkn->value[len - 1] = 0;
}

int ft_split_free(char ***sp)
{
	int idx;

	idx = 0;
	while ((*sp)[idx])
	{
		free((*sp)[idx]);
		idx++;
	}
	free(*sp);
	return (0);
}

size_t	ft_replace_envp_val(char *str, int i, char **item)
{
	int		dstlen;
	char 	*dst;

	dstlen = ft_strlen(str) + ft_strlen(item[1]) - (ft_strlen(item[0]) + 1);
	dst = (char *) ft_calloc(sizeof(char), (dstlen + 1));
	ft_strlcpy(dst, str, i + 1);
	ft_strlcpy(dst + i, item[1], ft_strlen(item[1]) + 1);
	ft_strlcpy(dst + i + ft_strlen(item[1]), \
               str + i + ft_strlen(item[0]) + 1, \
               dstlen - (i + ft_strlen(item[1])) + 1);
	free(str);
	str = ft_strdup(dst);
	free(dst);
	return (0);
}

size_t	ft_search_envp(t_token *tkn, int i, t_data *data)
{
	int		idx;
	int		envp_ord;
	char	**item;

	idx = i;
	envp_ord = 0;
	while (data->envp[envp_ord])
	{
		item = ft_split(data->envp[envp_ord], '=');
		if (ft_strncmp(tkn->value + idx + 1, item[0], ft_strlen(item[0])) == 0)
			ft_replace_envp_val(tkn->value, idx, item);
		envp_ord++;
	}
	printf("%s\n", tkn->value);
	return (0);
}


void	ft_set_valex(t_token *tkn, t_data *data)
{
	int 	idx;
	char 	*val;

	idx = 0;
	val = tkn->value;
	if (tkn->qt_status == 1)
	{
		tkn->valex = NULL;
		return ;
	}
		
	while (val[idx])
	{
		if (val[idx] == '$')
			ft_search_envp(tkn, idx, data);
		idx++;
	}
	printf("---\n");
}

size_t	 ft_lexer(t_data **data)
{
	t_token		*current;
	int			idx;

	(*data)->tkn = ft_tokenize((*data)->prompt);
	if (!(*data)->tkn)
		return (ft_print_ret("minishell: Tokenization failed\n", 2));
	idx = 0;
	current = (*data)->tkn->head;
	while (current)
	{
		ft_identify_token_type(current, (*data)->envp);
		if (current->qt_status != normal)
			ft_set_qt_value(current);
		ft_set_valex(current, *data);
		current->tkn_idx = idx++;
		current = current->next;
	}
	return (0);
}
