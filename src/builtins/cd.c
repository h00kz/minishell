#include "../../inc/minishell.h"

static void	update_pwd(t_cmds *cmds)
{
	char		*cur_path;
	t_envp		*envp;

	envp = cmds->lst_envp;
	cur_path = NULL;
	cur_path = getcwd(cur_path, 0);
	envp = ch_var_lst_envp(envp, "PWD", cur_path);
	free(cur_path);
	update_cmds_env(cmds);
}

static int	put_error(const char *file_name)
{
	g_exit_code = 1;
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
	return (1);
}

static char	*ft_getenv(const char *var, char **env)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = (int)ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_len))
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

static int	ch_dir(char *argv, t_cmds *cmds)
{
	char	*home;

	if (!argv)
	{
		home = ft_getenv("HOME", cmds->envp);
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_exit_code = 1;
			return (1);
		}
		if (chdir(home) < 0)
			return (put_error(home));
		else
			update_pwd(cmds);
	}
	else
	{
		if (chdir(argv) < 0)
			return (put_error(argv));
		else
			update_pwd(cmds);
	}
	return (0);
}

int	ft_cd(char *argv, char *opt, t_cmds *cmds)
{
	char	*old_pwd;

	(void)opt;
	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 0);
	cmds->lst_envp = ch_var_lst_envp(cmds->lst_envp, "OLDPWD", old_pwd);
	free(old_pwd);
	update_cmds_env(cmds);
	if (*opt)
	{
		g_exit_code = 2;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	ch_dir(argv, cmds);
	return (0);
}