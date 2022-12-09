#include "../../inc/minishell.h"

static t_envp	*update_pwd(t_envp *envp, char *dir, char *pwd)
{
	char	*str_update;

	str_update = ft_strjoin(pwd, dir);
	envp = ch_var_lst_envp(envp, "PWD", str_update);
	free(str_update);
	return (envp);
}

int	ft_cd(char *argv, t_envp *lst_envp)
{
	const char	*home;
	char		*cur_path;
	t_envp		*envp;

	envp = lst_envp;
	if (!argv)
	{
		home = getenv("HOME");
		if (chdir(home) < 0)
		{
			perror("cd");
			return (1);
		}
	}
	if (chdir(argv) < 0)
	{
		perror("cd");
		return (1);
	}
	else
	{
		cur_path = NULL;
		cur_path = getcwd(cur_path, 0);
		envp = ch_var_lst_envp(envp, "OLD_PWD", cur_path);
		envp = update_pwd(envp, argv, cur_path);
		free(cur_path);
	}
	return (0);
}