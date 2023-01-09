#include "../../inc/minishell.h"

int	make_cmd(t_cmds *cmd, char **input_split, int *i)
{
	free(cmd->cmd);
	cmd->cmd = ft_strdup(input_split[(*i)]);
	(*i)++;
	return (0);
}

int	make_file(t_cmds *cmd, char **input_split, int *i, int *n)
{
	cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
	(*i)++;
	(*n)++;
	return (0);
}

char	**vars(char **envp, char **input_split)
{
	int		i;
	char	**tmp;
	int		j;

	i = 0;
	j = 0;
	while (input_split[j])
		j++;
	tmp = malloc(sizeof(char *) * (j + 1));
	while (input_split[i])
	{
		tmp[i] = translate_env_vars(input_split[i], envp);
		free(input_split[i]);
		i++;
	}
	tmp[i] = NULL;
	free(input_split);
	return (tmp);
}


int	ft_parse_input_next(char **cmd_split, t_cmds *cmd,
	char *input, char **envp)
{
	char	**input_split;
	int		j;
	int		i;

	i = -1;
	while (cmd)
	{
		j = 0;
		input_split = ft_split_input(cmd_split[++i], ' ');
		while (input_split[j])
			j++;
		input_split = vars(envp, input_split);
		if (input_split == NULL)
		{
			ft_free_some_shit_2(input_split, j, input, cmd);
			return (1);
		}
		cmd = make_arg(input_split, j, cmd);
		ft_nfree_split(input_split, j);
		if (cmd == NULL)
			return (1);
		cmd = cmd->next;
	}
	ft_free_some_shit_3(input, cmd_split);
	return (0);
}

t_cmds	*parse_input(char *input, char **envp)
{
	char	**cmd_split;
	t_cmds	*cmd;
	int		pid;

	input = ft_str_add_space(input);
	cmd = ft_lstnew_node(envp);
	if (ft_check_redir(input) == 1 || input == NULL)
	{
		free(input);
		free_cmd(cmd);
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
		ft_fork(cmd, input, envp);
	else
		cmd = get_some_shit(cmd, input, envp, pid);
	cmd_split = ft_split_input(input, '|');
	if (ft_parse_input_next(cmd_split, cmd, input, envp) == 1)
	{
		free(input);
		ft_free_split(cmd_split);
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}