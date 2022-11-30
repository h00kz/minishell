/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:54:22 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:01:51 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*mem_dest;
	unsigned char	*mem_src;

	mem_src = (unsigned char *)src;
	mem_dest = (unsigned char *)dest;
	if (!dest && !src && n != 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		mem_dest[i] = mem_src[i];
		i++;
	}
	return (dest);
}
