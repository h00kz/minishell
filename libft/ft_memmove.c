/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:57:12 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:02:00 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*mem_dest;
	unsigned char	*mem_src;

	mem_src = (unsigned char *)src;
	mem_dest = (unsigned char *)dest;
	if (!dest && !src && n != 0)
		return (NULL);
	if (mem_dest > mem_src)
	{
		while (n > 0)
		{
			mem_dest[n - 1] = mem_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(mem_dest, mem_src, n);
	return (dest);
}
