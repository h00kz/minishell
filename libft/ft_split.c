/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:27:26 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:24:08 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char c, char const *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static size_t	ft_count_char(char c, char const *str)
{
	size_t	count;

	count = 0;
	while (str[count] != c && str[count])
		count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word_len;
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)ft_calloc(ft_count_word(c, s) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		word_len = ft_count_char(c, s + i);
		if (s[i] != c && s[i])
			strs[j++] = ft_substr(s, i, word_len);
		while (s[i] != c && s[i])
			i++;
	}
	return (strs);
}
