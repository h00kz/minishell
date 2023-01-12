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

char	**ft_make_double(char *s, char *s2, char **files)
{
	char	**str;
	char	**s2_split;
	int		i;
	int		j;

	j = 0;
	i = 0;
	str = ft_calloc(sizeof(char *), 1024);
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
	while (files[j])
	{
		str[i + j + 1] = files[j];
		j++;
	}
	str[i + j + 2] = NULL;
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
		execve(path, ft_make_double(cmd->cmd, cmd->args, cmd->file_name), cmd->envp);
	else if (!access(cmd->cmd, X_OK))
		execve(cmd->cmd, ft_make_double(cmd->cmd, cmd->args, cmd->file_name), cmd->envp);
	free(path);
}

void	ft_no_execve(t_cmds *cmd)
{
	close(0);
	close(1);
	close(2);
	close(cmd->pipe[0]);	
	free_cmd(cmd);
	exit(1);
}

// static void	ft_good_close(t_cmds *cmd)
// {
// 	close(cmd->pipe[0]);
// }

int	ft_no_dup(t_cmds *cmd)
{
	int fd;

	if (cmd->redir_out == PIPE && cmd->next)
	{
		ft_putendl_fd("\nNEXT\n\n", 2);
		return (cmd->next->pipe[1]);
	}
	if (cmd->outfile[0] != '\0')
	{
		ft_putendl_fd("\nOUTFILE\n\n", 2);
		fd = open(cmd->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	}
	return (fd);
}

void	ft_fork_execution(t_cmds *cmd)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (cmd)
	{
		ft_make_pipe(cmd);
		if (ft_is_builtins(cmd->cmd, cmd, cmd->envp) < 0)
		{
			pid = fork();
			if (pid == 0)
			{
				ft_dup(cmd, i);
				ft_close(cmd);
				ft_execve(cmd);
				ft_no_execve(cmd);
			}
			else
			{
				if (cmd->redir_in == PIPE && cmd->pipe[0] != -1)
					close(cmd->pipe[0]);
				cmd = cmd->next;
			}
			waitpid(pid, NULL, 0);
		}
		else
		{
			int fd = ft_no_dup(cmd);
			if (!ft_strncmp(cmd->cmd, "export", 6))
				ft_export(cmd->file_name, cmd->args, cmd, fd);
			if (!ft_strncmp(cmd->cmd, "cd", 2))
				ft_cd(cmd->file_name[0], cmd->args, cmd);
			if (!ft_strncmp(cmd->cmd, "echo", 4))
			{
				ft_dup(cmd, i);
				ft_echo(cmd->file_name, cmd->args);
				if (cmd->redir_in == PIPE && cmd->pipe[0] != -1)
					close(cmd->pipe[0]);
			}
			if (!ft_strncmp(cmd->cmd, "env", 3))
				ft_env(cmd->file_name, cmd->args, cmd);
			if (!ft_strncmp(cmd->cmd, "unset", 5))
				ft_unset(cmd->file_name, cmd->args, cmd);
			if (!ft_strncmp(cmd->cmd, "pwd", 3))
				ft_pwd(cmd->args);
			if (cmd->redir_in == PIPE && cmd->pipe[0] != -1)
				close(cmd->pipe[0]);
			cmd = cmd->next;
		}	
		i++;
	}
}