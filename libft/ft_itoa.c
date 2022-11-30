/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:13:05 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:01:18 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

static int	ft_count_digits(long int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	value;
	int			total_digits;

	value = n;
	total_digits = ft_count_digits(value);
	res = malloc(sizeof(char) * (total_digits + 1));
	if (!res)
		return (NULL);
	res[total_digits--] = '\0';
	if (value == 0)
		res[0] = '0';
	if (value < 0)
	{
		res[0] = '-';
		value = -value;
	}
	while (value > 0)
	{
		res[total_digits] = (value % 10) + 48;
		value /= 10;
		total_digits--;
	}
	return (res);
}
