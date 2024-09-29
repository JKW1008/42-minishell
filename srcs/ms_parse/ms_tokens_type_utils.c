/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_type_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:48:42 by kjung             #+#    #+#             */
/*   Updated: 2024/09/30 00:18:02 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_identify_token_type2(t_token *token)
{
	if (ft_strncmp(token->value, ">>", 2) == 0)
		token->token_type = l_dbl_greater;
	else if (ft_strncmp(token->value, "`", 1) == 0)
		token->token_type = l_bck_tick;
	else if (ft_strncmp(token->value, "\\", 1) == 0)
		token->token_type = l_bck_slash;
	else if (ft_strncmp(token->value, ";", 1) == 0)
		token->token_type = l_semicolon;
	else if (ms_ft_isspace(token->value[0]))
		token->token_type = l_space;
	else if (token->value[0] == '#')
		token->token_type = l_comment;
	else if (ft_strncmp(token->value, "&", 1) == 0)
		token->token_type = l_ampersand;
	else if (ft_strncmp(token->value, "(", 1) == 0)
		token->token_type = l_popen;
	else if (ft_strncmp(token->value, ")", 1) == 0)
		token->token_type = l_pclose;
	else
		token->token_type = l_word;
}

void	ft_identify_token_type(t_token *token, char **envp)
{
	size_t	len;

	len = ft_strlen(token->value);
	if (ft_is_builtin(token->value))
		token->token_type = l_word;
	else if (ft_is_command(token->value, envp))
		token->token_type = l_word;
	else if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
		token->token_type = l_quot_dbl;
	else if (len >= 2 && token->value[0] == '\'' && \
			token->value[len - 1] == '\'')
		token->token_type = l_quot_sgl;
	else if (ft_strncmp(token->value, "|", 1) == 0)
		token->token_type = l_pipe;
	else if (ft_strncmp(token->value, "<", 1) == 0)
		token->token_type = l_less;
	else if (ft_strncmp(token->value, ">", 1) == 0)
		token->token_type = l_greater;
	else if (ft_strncmp(token->value, "<<", 2) == 0)
		token->token_type = l_dbl_less;
	else
		ft_identify_token_type2(token);
}
