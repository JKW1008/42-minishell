/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:53:02 by kjung             #+#    #+#             */
/*   Updated: 2024/11/08 19:10:16 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"

//void	heredoc_sighandler(int sig)
//{
//	if (sig == SIGINT)
//	{
//		ft_global_err(130, 1);
//		write(STDOUT_FILENO, "^fuck\n", 6);
//		write(STDOUT_FILENO, 0, 1);
//	}
//}

//char	*get_input(char *prompt)
//{
//	char	*line;

//	line = readline(prompt);
//	//if (line && *line)
//	//	add_history(line);
//	return (line);
//}

//static int	reallocate_result(char **result, size_t *res_cap, \
//size_t needed_size)
//{
//	char	*new_result;
//	size_t	new_cap;

//	if (*res_cap == 0)
//		new_cap = 1024;
//	else
//		new_cap = *res_cap * 2;
//	while (new_cap < needed_size)
//		new_cap *= 2;
//	new_result = realloc(*result, new_cap);
//	if (!new_result)
//		return (0);
//	*result = new_result;
//	*res_cap = new_cap;
//	return (1);
//}

//static int process_heredoc_line(char *delimiter, char **result, \
//size_t *res_len, size_t *res_cap)
//{
//    char    *line;
//    size_t  line_len;

//	if (ft_global_err(0, 0))
//		return (0);
//    line = get_input("> ");
//	if (!line || ft_global_err(0, 0))  // Ctrl+D나 EOF
//    {
//		free(line);
//		return (0);
//	}
    
//    // delimiter와 정확히 일치할 때만 종료 (길이와 내용 모두 같아야 함)
//	printf("line : %s, delim = %s\n", line, delimiter);
//    if (ft_strlen(line) == ft_strlen(delimiter) && 
//        ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
//    {
//        free(line);
//        return (0);
//    }
    
//    line_len = ft_strlen(line);
//    if (*result == NULL)
//    {
//        *res_cap = line_len + 2;
//        *result = (char *)malloc(*res_cap);
//        if (!*result)
//        {
//            free(line);
//            return (0);
//        }
//    }
//    else if (*res_len + line_len + 2 > *res_cap)
//    {
//        if (!reallocate_result(result, res_cap, *res_len + line_len + 2))
//        {
//            free(line);
//            return (0);
//        }
//    }
//    ft_strlcpy(*result + *res_len, line, line_len + 1);
//    *res_len += line_len;
//    (*result)[(*res_len)++] = '\n';
//    (*result)[*res_len] = '\0';
//    free(line);
//    return (1);
//}

//char    *set_heredoc_old(t_cmd *node, int *here_idx)
//{
//    char    *result;
//    char    *delimiter;
//    size_t  res_len;
//    size_t  res_cap;
//	int		i;

//	i = 0;
//	while (i < node->rdr_cnt)
//	{
//		if (node->rdr[i]->type == RD_HEREDOC)
//		{
//			delimiter = node->rdr[i]->file;
//			break ;
//		}
//		i++;
//	}
//    result = NULL;
//    res_len = 0;
//    res_cap = 0;
//	*here_idx = i;

//	void (*old_handler)(int) = signal(SIGINT, heredoc_sighandler);
//    while (!ft_global_err(0, 0))
//    {
//        if (!process_heredoc_line(delimiter, &result, &res_len, &res_cap))
//        {
//			printf("ft_err %zu\n", ft_global_err(0, 0));
//			if (ft_global_err(0, 0) > 0)
//			{
//				free(result);
//				result = NULL;
//			}
//			break ;
//		}
//    }
//	signal(SIGINT, old_handler);
//	ft_ctrl_signal();
//	if (ft_global_err(0, 0) && result)
//	{
//		free(result);
//		result = NULL;
//	}
//    return (result);
//}

//void process_commands_old(t_data **data, t_heredoc_list *heredoc_list)
//{
//    t_cmd   *tmp;
//    char    *here_doc;
//    int     i;
//	int		here_idx;

//    i = 1;
//	if (ft_global_err(0, 0) != 0)
//		return ;
//    while (i <= (*data)->cmdline->count)
//    {
//        tmp = (*data)->cmdline->head;
//        while (tmp && tmp->prompt)
//        {
//            if (tmp->ord == i && tmp->is_heredoc)
//            {
//                here_doc = set_heredoc(tmp, &here_idx);
//                if (here_doc && heredoc_list->count < MAX_HEREDOCS)
//                {
//                    if (tmp->rdr_cnt)
//                    {
//                        heredoc_list->heredocs[heredoc_list->count].content = here_doc;
//                        heredoc_list->heredocs[heredoc_list->count].delimiter = \
//                        ft_strdup(tmp->rdr[here_idx]->file);
//                        heredoc_list->count++;
//                    }
//                    else
//                    {
//                        free(here_doc);  // args[0]가 NULL이면 here_doc 해제
//                    }
//                }
//                else
//                    free(here_doc);
//            }
//            tmp = tmp->next;
//        }
//        i++;
//    }
//}
