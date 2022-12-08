/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:27:26 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/12/07 13:44:47 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_count_word_split(char c, char const *str)
{
	int	count;
	int	i;
	int	boolean;

	i = 0;
	count = 0;
	boolean = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while ((str[i] != c || boolean == 1) && str[i])
		{
			if (str[i] == '"' && boolean == 0)
				boolean = 1;
			else if (str[i] == '"' && boolean == 1)
				boolean = 0;
			i++;
		}
	}
	return (count);
}

static size_t	ft_count_char_split(char c, char const *str)
{
	size_t	count;
	int		boolean;

	boolean = 0;
	count = 0;
	while ((str[count] != c || boolean == 1) && str[count])
	{
		if (str[count] == '"' && boolean == 0)
			boolean = 1;
		else if (str[count] == '"' && boolean == 1)
			boolean = 0;
		count++;
	}
	return (count);
}

void	ft_skip_char(char const *s, size_t *i, int *boolean, char c)
{
	while (s[(*i)] && (s[(*i)] != c || (*boolean) == 1))
	{
		if (s[(*i)] == '"' && (*boolean) == 0)
			(*boolean) = 1;
		else if (s[(*i)] == '"' && (*boolean) == 1)
			(*boolean) = 0;
		(*i)++;
	}
}

char	**ft_split_input(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word_len;
	int		boolean;
	char	**strs;

	boolean = 0;
	if (!s)
		return (NULL);
	strs = ft_calloc(ft_count_word_split(c, s) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		word_len = ft_count_char_split(c, s + i);
		if (s[i] != c && s[i])
			strs[j++] = ft_substr(s, i, word_len);
		ft_skip_char(s, &i, &boolean, c);
	}
	return (strs);
}
