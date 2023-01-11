#include "../../inc/minishell.h"

char	*ft_get_path(t_cmds *cmd, char *path)
{
	char	**paths;
	char	*check_path;
	char	*tmp;
	int		i;

	i = -1;
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		check_path = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin_free_choice(check_path, cmd->cmd, 1);
		if (!access(tmp, X_OK) || !access(cmd->cmd, X_OK))
		{
			ft_free_split(paths);
			return (tmp);
		}
		free(tmp);
	}
	ft_free_split(paths);
	return (NULL);
}

char	**ft_make_double(char *s, char *s2)
{
	char	**str;
	char	**s2_split;
	int		i;

	i = 0;
	str = ft_calloc(sizeof(char *), 64);
	str[0] = s;
	if (!*s2)
		str[1] = NULL;
	else
	{
		s2_split = ft_split(s2, ' ');
		while (s2_split[i])
		{
			str[i + 1] = s2_split[i];
			i++;
		}
	}
	str[i + 2] = NULL;
	return (str);
}

void	ft_execve(t_cmds *cmd)
{
	char	*path;
	char	*tmp;

	tmp = ft_getenv("PATH", cmd->envp);
	path = ft_get_path(cmd, tmp);
	if (path == NULL)
	{
		free(path);
		ft_putendl_fd("TAMER CA MARCH PO", 2);
		return ;
	}
	else if (!access(path, X_OK))
		execve(path, ft_make_double(cmd->cmd, cmd->args), cmd->envp);
	else if (!access(cmd->cmd, X_OK))
		execve(cmd->cmd, ft_make_double(cmd->cmd, cmd->args), cmd->envp);
	free(path);
}

void	ft_no_execve(t_cmds *cmd)
{
	close(0);
	close(1);
	close(2);
	free_cmd(cmd);
	exit(1);
}

void	ft_first_close(t_cmds *cmd)
{
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

void	ft_fork_execution(t_cmds *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		ft_make_pipe(cmd);
		pid = fork();
		if (pid == 0)
		{
			ft_dup(cmd);
			ft_close(cmd);
			ft_execve(cmd);
			ft_no_execve(cmd);
		}
		else
			cmd = cmd->next;
		waitpid(pid, NULL, 0);
	}
}