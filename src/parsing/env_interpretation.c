#include "minishell.h"

char	*ft_translate(char **envp, char *input)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (input[i] && ft_isalnum(input[i]))
		i++;
	while (envp[j] && ft_strncmp(envp[j], &input[1], i - 1) != 0)
		j++;
	if (envp[j] && envp[j][i - 1] == '=')
		str = ft_strdup(&envp[j][i]);
	else
		return (NULL);
	return (str);
}

int	ft_check(char **input, int *i, char **str, int boolean)
{
	int	check;

	check = 0;
	if (ft_strncmp(&(*input)[(*i)], "$\"", 2) == 0)
	{
		(*str) = ft_strjoin_free((*str), "$");
		(*i)++;
		check = 1;
	}
	else if (ft_strncmp(&(*input)[(*i)], "$?", 2) == 0 && boolean != 2)
	{
		(*str) = ft_strjoin_free_choice((*str), ft_itoa(g_exit_code), 3);
		(*i) += 2;
		check = 1;
	}
	else if (ft_strncmp(&(*input)[(*i)], "$", 1) == 0
		&& ft_isalnum((*input)[(*i) + 1]) == 0)
	{
		(*str) = ft_strjoin_free((*str), "$");
		(*i)++;
		check = 1;
	}
	return (check);
}

int	ft_last_check(char *input, int boolean, char **tmp, int *i)
{
	int	check;

	check = 0;
	if (input[(*i)])
	{
		if (input[(*i)] != '"' || boolean == 2)
		{
			(*tmp) = ft_calloc(sizeof(char), 2);
			(*tmp)[0] = input[(*i)];
			check = 1;
		}
		(*i)++;
	}
	return (check);
}

void	ft_translate_env_next(int *i, char *tmp, char *input, char **str)
{
	(*i)++;
	if (tmp)
		(*i)++;
	while (input[(*i)] && ft_isalnum(input[(*i)]))
		(*i)++;
	if (tmp)
	{
		(*str) = ft_strjoin_free((*str), tmp);
		free(tmp);
	}
}
