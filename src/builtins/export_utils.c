#include "../../inc/minishell.h"
 
int	ft_check_double_var(t_envp *env, char *arg)
{
	while (env)
	{
		if (ft_str_index_chr(arg, '=') == -1)
		{
			if (!ft_strcmp(env->variable, arg))
				return (0);
		}
		else
			if (!ft_strncmp(env->variable, arg, (int)ft_strlen(env->variable)))
				return (0);
		env = env->next;
	}
	return (1);
}
