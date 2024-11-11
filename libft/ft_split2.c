/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:04:36 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/11 13:04:38 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	count_word2(char const *s, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	if (!s[0])
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			cnt++;
		i++;
	}
	if (s[0] != c)
		cnt++;
	return (cnt);
}

static int	next_ptr(char const *ptr, char c, int is_delimiter)
{
	int	i;

	i = 0;
	if (is_delimiter)
		ptr++;
	while (*ptr && *ptr != c)
	{
		i++;
		ptr++;
	}
	return (i + 1);
}

char	*get_word2(char const *s, char c)
{
	int		idx;
	int		len;
	char	*word;

	idx = 0;
	len = next_ptr(s, c, 1);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (idx < len)
		word[idx++] = *s++;
	word[idx] = '\0';
	return (word);
}

static char	**free_arr(char **words, int idx)
{
	while (idx > 0)
		free(words[--idx]);
	free(words);
	return (NULL);
}

char	**ft_split2(char const *s, char c)
{
	int		idx_word;
	int		len_words;
	char	**words;

	if (!s)
		return (NULL);
	idx_word = 0;
	len_words = count_word2(s, c);
	words = (char **)malloc(sizeof(char *) * (len_words + 1));
	if (!words)
		return (NULL);
	while (idx_word < len_words)
	{
		words[idx_word] = get_word2(s, c);
		if (!words[idx_word])
			return (free_arr(words, idx_word));
		s += ft_strlen(words[idx_word]);
		idx_word++;
	}
	words[idx_word] = NULL;
	return (words);
}

//#include <stdio.h>
//int main(void)
//{
//	char **sp = ft_split2("$a$b$c", '$');
//	while (*sp)
//		printf("%s\n", *sp++);
//	printf("\n\n\n");
//	sp = ft_split2("abc", '$');
//	while (*sp)
//		printf("%s\n", *sp++);
//	printf("\n\n\n");
//	sp = ft_split2("$a$$b$c$", '$');
//	while (*sp)
//		printf("%s\n", *sp++);
//	printf("\n\n\n");
//	sp = ft_split2("a$b$c", '$');
//	while (*sp)
//		printf("%s\n", *sp++);
//}
