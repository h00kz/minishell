/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:31:09 by jlarrieu          #+#    #+#             */
/*   Updated: 2022/09/30 14:02:16 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	value;

	value = (long int)n;
	if (value < INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (value < 0)
	{
		ft_putchar_fd('-', fd);
		value = -value;
	}
	if (value > 9)
		ft_putnbr_fd(value / 10, fd);
	ft_putchar_fd((value % 10) + 48, fd);
}
