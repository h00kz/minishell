/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlen.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pdubacqu <pdubacqu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/26 13:17:21 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/07 14:30:08 by pdubacqu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}
