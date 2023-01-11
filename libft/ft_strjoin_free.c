/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin_free.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pdubacqu <pdubacqu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/06 17:32:24 by jlarrieu		  #+#	#+#			 */
/*   Updated: 2022/12/07 15:45:09 by pdubacqu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str(char *s1, char *s2, int who_free)
{
	if (who_free == 1)
	{
		free(s1);
		s1 = NULL;
	}
	if (who_free == 2)
		free(s2);
	if (who_free == 3)
	{
		free(s2);
		free(s1);
	}
}

char	*ft_strjoin_free_choice(char *s1, char *s2, int who_free)
{
	size_t	strs_len;
	size_t	i;
	char	*str;

	i = 0;
	strs_len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(strs_len + 1, sizeof(char));
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	i = 0;
	while (s2[i] && i < strs_len)
	{
		str[i + ft_strlen(s1)] = s2[i];
		++i;
	}
	ft_free_str(s1, s2, who_free);
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	strs_len;
	size_t	i;
	char	*str;

	i = 0;
	strs_len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(strs_len + 1, sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	i = 0;
	while (s2[i] && i < strs_len)
	{
		str[i + ft_strlen(s1)] = s2[i];
		++i;
	}
	free(s1);
	return (str);
}
