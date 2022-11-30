/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:40:02 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:05:19 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		s_m_start;

	if (!s)
		return (NULL);
	s_m_start = (ft_strlen(s) - start);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
	{
		str = (char *)ft_calloc(s_m_start + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, s + start, (s_m_start + 1));
		return (str);
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
