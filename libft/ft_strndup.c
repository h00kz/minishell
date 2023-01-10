/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strndup.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/27 11:34:22 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/09/30 11:19:28 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)ft_calloc(n + 1, sizeof(char));
	if (!str || !s)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
