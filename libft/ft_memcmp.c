/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:41:19 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:01:44 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	i = 0;
	mem_s1 = (unsigned char *)s1;
	mem_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((mem_s1[i] == mem_s2[i]) && i < n - 1)
		i++;
	return ((int)(mem_s1[i] - mem_s2[i]));
}
