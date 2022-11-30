/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:53:36 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:02:45 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	strs_len;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	strs_len = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)ft_calloc(strs_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[i + ft_strlen(s1)] = s2[i];
	str[strs_len] = '\0';
	return (str);
}
