#include "../../inc/minishell.h"

char	**ft_cpy_envp(char **envp)
{
	char **new_envp;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	new_envp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

int	ft_env(char **argv, char *opt, t_cmds *cmd)
{
	int	i;

	i = 0;
	g_exit_code = 0;
	update_cmds_env(cmd);
	if (!*argv && !*opt)
	{
		while (cmd->envp[i] != NULL)
		{
			ft_putendl_fd(cmd->envp[i], 1);
			i++;
		}
		return (0);
	}
	if (*opt)
	{
		g_exit_code = 125;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putendl_fd(": invalid option", 2);
		return (125);
	}
	else if (*argv)
	{
		g_exit_code = 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	return (0);
}