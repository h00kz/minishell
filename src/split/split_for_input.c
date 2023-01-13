/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:25:31 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:25:32 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_bool_split(const char *str, int i, int boolean)
{
	if (str[i] == '"' && boolean == 0)
		boolean = 1;
	else if (str[i] == '"' && boolean == 1)
		boolean = 0;
	else if (str[i] == '\'' && boolean == 0)
		boolean = 3;
	else if (str[i] == '\'' && boolean == 3)
		boolean = 0;
	return (boolean);
}

static size_t	ft_count_char_split(char c, char const *str)
{
	size_t	count;
	int		boolean;

	boolean = 0;
	count = 0;
	while ((str[count] != c || boolean == 1 || boolean == 3) && str[count])
	{
		if (str[count] == '"' && boolean == 0)
			boolean = 1;
		else if (str[count] == '"' && boolean == 1)
			boolean = 0;
		else if (str[count] == '\'' && boolean == 0)
			boolean = 3;
		else if (str[count] == '\'' && boolean == 3)
				boolean = 0;
		count++;
	}
	return (count);
}

void	ft_skip_char(char const *s, size_t *i, int *boolean, char c)
{
	while (s[(*i)] && (s[(*i)] != c || (*boolean) == 1 || (*boolean) == 3))
	{
		if (s[(*i)] == '"' && (*boolean) == 0)
			(*boolean) = 1;
		else if (s[(*i)] == '"' && (*boolean) == 1)
			(*boolean) = 0;
		else if (s[(*i)] == '\'' && (*boolean) == 0)
			(*boolean) = 3;
		else if (s[(*i)] == '\'' && (*boolean) == 3)
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
	strs[j] = NULL;
	return (strs);
}
