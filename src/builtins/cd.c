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
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
	return (1);
}

int	ft_cd(char *argv, char *opt, t_cmds *cmds)
{
	char	*home;
	char	*old_pwd;

	(void)opt;
	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 0);
	cmds->lst_envp = ch_var_lst_envp(cmds->lst_envp, "OLDPWD", old_pwd);
	free(old_pwd);
	update_cmds_env(cmds);
	if (!argv)
	{
		home = getenv("HOME");
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