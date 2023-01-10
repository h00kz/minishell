/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/21 11:14:40 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/11/30 16:00:53 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char	*s;
	char	*c;
	int		ret;

	s = ft_calloc(sizeof(char), 10000);
	c = s;
	ret = read(fd, c, 1);
	while (ret > 0 && *c != '\n')
	{
		c++;
		ret = read(fd, c, 1);
	}
	if (*c == '\n')
		c++;
	if (c > s)
	{
		*c = 0;
		return (s);
	}
	free(s);
	return (NULL);
}
