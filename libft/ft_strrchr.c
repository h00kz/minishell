/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:30:10 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:03:35 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)&s[s_len]);
	while (s_len-- > 0)
	{
		if ((char)c == s[s_len])
			return ((char *)&s[s_len]);
	}
	return (NULL);
}
