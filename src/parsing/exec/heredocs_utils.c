#include "../../../inc/minishell.h"

t_cmds	*ft_make_here_doc(char *input, char **envp)
{
	int		i;
	char	**input_split;
	t_cmds	*cmd;
	t_cmds	*save;

	i = 0;
	input_split = ft_make_input_split(input, envp);
	cmd = ft_lstnew_node(envp);
	save = cmd;
	while (input_split && input_split[i])
	{
		if (ft_strcmp(input_split[i], "|") == 0)
		{
			ft_lstadd_back_cmd(&cmd, ft_lstnew_node(envp));
			cmd = cmd->next;
		}
		if (ft_make_here_doc_next(input_split, cmd, &i) == 1)
			return (NULL);
		i++;
	}
	ft_free_split(input_split);
	return (save);
}

t_cmds	*ft_get_heredoc_in(char *input, char **envp)
{
	int		i;
	char	**input_split;
	t_cmds	*cmd;
	t_cmds	*save;

	i = 0;
	input_split = ft_make_input_split(input, envp);
	cmd = ft_lstnew_node(envp);
	save = cmd;
	while (input_split && input_split[i])
	{
		if (ft_strcmp(input_split[i], "|") == 0)
		{
			ft_lstadd_back_cmd(&cmd, ft_lstnew_node(envp));
			cmd = cmd->next;
		}
		if (ft_get_heredoc_in_next(input_split, cmd, &i) == 1)
			return (cmd);
		i++;
	}
	ft_free_split(input_split);
	return (save);
}

void	ft_get_here_doc_in(t_cmds *cmd, int *i)
{
	char	*tmp_in;

	tmp_in = ft_strjoin_free_choice(".heredoc", ft_itoa((*i)), 2);
	free(cmd->heredoc_in);
	cmd->heredoc_in = tmp_in;
	(*i)++;
}

int	ft_get_heredoc_in_next(char **input_split, t_cmds *cmd, int *i)
{
	if (ft_strncmp(input_split[(*i)], "<<", 2) == 0)
		ft_get_here_doc_in(cmd, i);
	else if (ft_strncmp(input_split[(*i)], "<", 1) == 0)
	{
		if (ft_left_redir(input_split, i) == 1)
		{
			ft_free_some_shit4(input_split);
			return (1);
		}
	}
	return (0);
}


int	ft_make_here_doc_next(char **input_split, t_cmds *cmd, int *i)
{
	if (ft_strncmp(input_split[(*i)], "<<", 2) == 0)
		ft_make_heredoc_in(cmd, input_split, i);
	else if (ft_strncmp(input_split[(*i)], "<", 1) == 0)
	{
		if (ft_left_redir(input_split, i) == 1)
		{
			ft_free_some_shit(input_split, cmd);
			return (1);
		}
	}
	return (0);
}