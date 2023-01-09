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

char	*ft_get_vars(char *input)
{
	char	*str;
	int		i;

	i = 0;
	while (input[i] && input[i] != '\'')
		i++;
	str = ft_strndup(input, i);
	return (str);
}

char	*translate_vars(char *input, int *i, char **envp, int *boolean)
{
	char	*str;

	if ((*boolean) != 2)
		str = ft_translate(envp, &input[(*i)]);
	else if ((*boolean) == 2)
		return (ft_get_vars(&input[(*i)]));
	return (str);
}

int	ft_check_bool_vars(char *input, int *i, int *boolean, int verif)
{
	int	check;

	check = 0;
	if (input[(*i)] == '"' && (*boolean) == 0)
		(*boolean) = 1;
	else if (input[(*i)] == '"' && (*boolean) == 1)
		(*boolean) = 0;
	else if (input[(*i)] == '\'' && (*boolean) == 0)
		(*boolean) = 2;
	else if (input[(*i)] == '\'' && (*boolean) == 2)
		(*boolean) = 0;
	if ((*boolean) != verif)
		check = 1;
	if (check == 1)
		(*i)++;
	return (check);
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

char	*translate_env_vars(char *input, char **envp)
{
	char	*str;
	char	*tmp;
	int		boolean;
	int		i;

	i = 0;
	boolean = 0;
	str = NULL;
	while (input && input[i])
	{
		if (ft_check_bool_vars(input, &i, &boolean, boolean) == 0)
		{
			if (ft_check(&input, &i, &str, boolean) == 0)
			{
				if (input[i] == '$' && boolean != 2)
				{
					tmp = translate_vars(input, &i, envp, &boolean);
					ft_translate_env_next(&i, tmp, input, &str);
				}
				else if (ft_last_check(input, boolean, &tmp, &i) == 1)
					str = ft_strjoin_free_choice(str, tmp, 3);
			}
		}
	}
	return (str);
}
