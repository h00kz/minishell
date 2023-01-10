/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pdubacqu <pdubacqu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/27 10:33:13 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/07 13:47:09 by pdubacqu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;
	size_t			i;

	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((s1_uc[i] == s2_uc[i]) && (s1_uc[i] && s2_uc[i]) && i < n - 1)
		i++;
	return (s1_uc[i] - s2_uc[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;
	int				i;

	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while ((s1_uc[i] == s2_uc[i]) && (s1_uc[i] && s2_uc[i]))
		i++;
	return (s1_uc[i] - s2_uc[i]);
}
