/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_str_isdigits.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/26 11:55:08 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/14 16:36:29 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isdigits(const char *s)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
