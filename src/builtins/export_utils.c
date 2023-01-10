#include "../../inc/minishell.h"
 
int	ft_check_double_var(t_envp *env)
{
	t_envp *cur;

	cur = env->next;
	while (env && cur->next)
	{
		if (!ft_strcmp(env->variable, cur->variable))
			return (0);
		else
		{
			cur = cur->next;
			continue ;
		}
		env = env->next;
	}
	return (1);
}
