#include "../../inc/minishell.h"
 
int	ft_check_double_var(t_envp *env, char *arg)
{
	while (env)
	{
		if (!ft_strncmp(env->variable, arg, (int)ft_strlen(env->variable)))
			return (0);
		env = env->next;
	}
	return (1);
}
