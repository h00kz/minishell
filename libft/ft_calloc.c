/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:59:55 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:00:08 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem_block;

	if (nmemb == 0 || size == 0)
	{
		mem_block = (unsigned char *)ft_calloc(sizeof(unsigned char), 1);
		ft_bzero(mem_block, 1);
		return (mem_block);
	}
	if (nmemb > 2147483647 || size > 2147483647)
		return (NULL);
	if ((nmemb * size) > 2147483647)
		return (NULL);
	mem_block = malloc(sizeof(unsigned char) * (nmemb * size));
	if (!mem_block)
		return (NULL);
	ft_bzero(mem_block, (nmemb * size));
	return (mem_block);
}
