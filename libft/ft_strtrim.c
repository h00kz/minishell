/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:06:35 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 15:19:45 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		end;
	size_t		start;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_is_charset(s1[start], set))
		start++;
	while (ft_is_charset(s1[end - 1], set) && end > start)
		end--;
	str = ft_substr(s1, start, end - start);
	if (!str)
		return (NULL);
	return (str);
}
