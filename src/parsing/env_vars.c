/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:25:47 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:25:48 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
