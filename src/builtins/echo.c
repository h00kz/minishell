


#include "../../inc/minishell.h"

int	ft_check_echo(char *input_split)
{
	int	i;

	i = 0;
	while (input_split[i])
	{
		if (input_split[i] != '-' && input_split[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}