/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:24:45 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:24:46 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_plus(char *arg, int sep_i, t_envp *env)
{
	if (arg[sep_i - 1] == '+' && arg[sep_i + 1] != 0)
	{
		if (env->value)
			env->value = ft_strjoin_free_choice(env->value, arg + sep_i + 1, 1);
		else
			env->value = ft_strdup(arg + sep_i + 1);
		return (0);
	}
	return (1);
}

int	ft_assign_value(t_envp *env, char *arg, int sep_i)
{
	if (ft_strncmp(env->variable, arg, sep_i) == 0)
	{
		if (env->value)
		{
			free(env->value);
			env->value = ft_strdup(arg + sep_i + 1);
		}
		else
			env->value = ft_strdup(arg + sep_i + 1);
		return (0);
	}
	return (1);
}

int	ft_check_double_var(t_envp *env, char *arg)
{
	int	sep_i;

	while (env)
	{
		sep_i = ft_str_index_chr(arg, '=');
		if (sep_i < 0)
		{
			if (!ft_strcmp(env->variable, arg))
				return (0);
		}
		else
		{
			if (!ft_strncmp(env->variable, arg, sep_i - 1))
				if (ft_check_plus(arg, sep_i, env) == 0)
					return (0);
			if (ft_assign_value(env, arg, sep_i) == 0)
				return (0);
		}
		env = env->next;
	}
	return (1);
}

char	*get_first_ascii(t_envp *envp)
{
	char	*first_ascii;

	first_ascii = ft_calloc(sizeof(char *), 2);
	first_ascii[0] = 127;
	while (envp)
	{
		if (ft_strcmp(first_ascii, envp->variable) > 0 && envp->print == 0)
		{
			if (first_ascii[0] == 127)
				free(first_ascii);
			first_ascii = envp->variable;
		}
		envp = envp->next;
	}
	return (first_ascii);
}

int	ft_check_print(t_envp *envp)
{
	while (envp)
	{
		if (envp->print == 0)
			return (0);
		else
			envp = envp->next;
	}
	return (1);
}
