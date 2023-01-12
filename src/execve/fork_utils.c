#include "../../inc/minishell.h"

void	ft_fork_exec(t_cmds *cmd, int i, t_cmds *save)
{
	ft_dup(cmd, i);
	ft_close(cmd);
	ft_execve(cmd);
	ft_no_execve(save);
}

void	ft_no_fork(t_cmds *cmd, int pid)
{
	if (cmd->redir_in == PIPE && cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	waitpid(pid, &g_exit_code[0], 0);
	g_exit_code[0] >>= 8;
}

int	ft_no_dup(t_cmds *cmd)
{
	int	fd;

	fd = 1;
	if (cmd->redir_out == PIPE && cmd->next)
		return (cmd->next->pipe[1]);
	if (cmd->outfile[0] != '\0')
		fd = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	return (fd);
}

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

void	ft_copy(char **files, int *j, int i, char ***str)
{
	while (files[*j])
	{
		*str[i + (*j) + 1] = files[(*j)];
		(*j)++;
	}
}
