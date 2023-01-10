/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/27 10:53:48 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/14 16:38:01 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	long long int	value;

	i = 0;
	sign = 1;
	value = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign *= -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value = value * 10 + (nptr[i] - 48);
		i++;
	}
	return ((int)(value * sign));
}
