/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_export_isalnum.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jlarrieu <jlarrieu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/26 11:55:08 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/13 18:01:03 by jlarrieu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_export_isalnum(const char *s)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if ((!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '='))
			return (0);
		i++;
	}
	return (1);
}
