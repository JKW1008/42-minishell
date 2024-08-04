/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:00 by jaehukim          #+#    #+#             */
/*   Updated: 2024/08/04 16:46:01 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_escape_append(void)
{

}

 
// ls abc "asdf asdf zxcv qwer " \\ 

static void	token_classifier(char *word)
{
	int	i;

	i = 0;
	while (i < ft_strlen(word))
	{
		if (!ft_isalnum(word[i++]))
	}

}


static t_tkn_stk *tokenizer(char *prompt, t_tkn_stk **tkns)
{
	int			idx;
	char		**words;
	t_tkn_stk	*tokns;

	idx = 0;
	words = ft_split(prompt, ' ');
	while (words[idx])
	{

	}

}


void	ft_init_stk_tokens(t_tkn_stk **tkns)
{
	*tkns = (t_tkn_stk *) malloc(sizeof(t_tkn_stk));
	(*tkns)->head = NULL;
	(*tkns)->tail = NULL;
	(*tkns)->__len__ = 0;
}

size_t	ft_lexer(char *prompt)
{
	int		len;
	t_tkn_stk	*tokens;

	ft_init_stk_tokens(&tokens);
	tokens = ft_tokenizer(prompt);
}
