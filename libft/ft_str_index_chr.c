/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_str_index_chr.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/27 10:28:00 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/09/30 14:02:35 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_str_index_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (c == s[i])
		return (i);
	return (-1);
}
