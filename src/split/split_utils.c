#include "../../inc/minishell.h"

void	ft_free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_nfree_split(char **strs, int n)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_count_word_split(char c, char const *str)
{
	int	count;
	int	i;
	int	boolean;

	i = 0;
	count = 0;
	boolean = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while ((str[i] != c || boolean == 1 || boolean == 3) && str[i])
		{
			boolean = ft_check_bool_split(str, i, boolean);
			i++;
		}
	}
	return (count);
}
