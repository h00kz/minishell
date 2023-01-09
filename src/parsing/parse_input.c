#include "../../inc/minishell.h"

int	ft_check_bool_redir(int boolean, int *i, char *input)
{
	if (input[(*i)] == '"' && boolean == 0)
	{
		boolean = 1;
		(*i)++;
	}
	else if (input[(*i)] == '"' && boolean == 1)
	{
		boolean = 0;
		(*i)++;
	}
	else if (input[(*i)] == '\'' && boolean == 0)
	{
		boolean = 2;
		(*i)++;
	}
	else if (input[(*i)] == '\'' && boolean == 2)
	{
		boolean = 0;
		(*i)++;
	}
	return (boolean);
}

int	ft_make_redir_pipe(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '|')
		{
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_make_redir_left(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '<')
		{
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_make_redir_right(char *input, int *i)
{
	(*i)++;
	while (input && input[(*i)] && (input[(*i)] == ' ' || input[(*i)] == '\t'))
	{
		(*i)++;
		if (input && input[(*i)] && input[(*i)] == '>')
		{
			printf("syntax error\n");
			return (1);
		}
	}
	if (!(input[(*i)]))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_check_redir(char *input)
{
	int	i;
	int	boolean;
	int	error;

	boolean = 0;
	i = 0;
	error = 0;
	while (i < (int)ft_strlen(input))
	{
		boolean = ft_check_bool_redir(boolean, &i, input);
		if (input && input[i] == '|' && boolean != 2 && boolean != 1)
			error = ft_make_redir_pipe(input, &i);
		else if (input && input[i] == '<' && boolean != 2 && boolean != 1)
			error = ft_make_redir_left(input, &i);
		else if (input && input[i] == '>' && boolean != 2 && boolean != 1)
			error = ft_make_redir_right(input, &i);
		else
			i++;
		if (error != 0)
			return (error);
	}
	return (0);
}

int	ft_strlen_sep(char *str)
{
	int	i;
	int	j;
	int	boolean;

	i = 0;
	j = 0;
	boolean = 0;
	while (str[i])
	{
		if (str[i] == '\"' && boolean == 0)
			boolean = 1;
		else if (str[i] == '\'' && boolean == 0)
			boolean = 2;
		else if (str[i] == '\'' && boolean == 2)
			boolean = 0;
		else if (str[i] == '\"' && boolean == 1)
			boolean = 0;
		if ((boolean == 0 || boolean == 2)
			&& (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			j += 2;
		i++;
		j++;
	}
	return (j);
}

int	ft_check_bool(char *str, int i, int boolean)
{
	if (str[i] == '\"' && boolean == 0)
		boolean = 1;
	else if (str[i] == '\'' && boolean == 0)
		boolean = 2;
	else if (str[i] == '\'' && boolean == 2)
		boolean = 0;
	else if (str[i] == '\"' && boolean == 1)
		boolean = 0;
	return (boolean);
}

char	*add_space_heredoc(char *str, char *s, int *i, int *j)
{
	s[(*j)] = ' ';
	(*j)++;
	s[(*j)] = str[(*i)];
	(*j)++;
	(*i)++;
	s[(*j)] = str[(*i)];
	(*j)++;
	s[(*j)] = ' ';
	return (s);
}

char	*add_space(char *str, char *s, int i, int *j)
{
	s[(*j)] = ' ';
	(*j)++;
	s[(*j)] = str[i];
	(*j)++;
	s[(*j)] = ' ';
	return (s);
}

int	ft_check_add_space(int j, char *str, int i, int boolean)
{
	if (j == 1)
		return ((boolean == 0 || boolean == 2)
			&& ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>')));
	else
		return ((boolean == 0 || boolean == 2)
			&& (str[i] == '<' || str[i] == '>' || str[i] == '|'));
}

char	*ft_str_add_space(char *str)
{
	int		i;
	int		j;
	char	*s;
	int		boolean;

	boolean = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	s = ft_calloc(sizeof(char), ft_strlen_sep(str) + 2);
	while (str[i])
	{
		boolean = ft_check_bool(str, i, boolean);
		if (ft_check_add_space(1, str, i, boolean))
			s = add_space_heredoc(str, s, &i, &j);
		else if (ft_check_add_space(0, str, i, boolean))
			s = add_space(str, s, i, &j);
		else
			s[j] = str[i];
		j++;
		i++;
	}
	s[ft_strlen_sep(str) + 1] = '\0';
	return (s);
}

int	make_left_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (input_split[(*i) + 1])
	{
		cmd->fd_file = open(input_split[(*i) + 1], O_RDONLY);
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
		cmd->redir_in = L_REDIR;
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->infile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

int	make_right_redir(t_cmds *cmd, char **input_split, int *i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->redir_out = R_REDIR;
	if (input_split[(*i) + 1])
	{
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->infile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
		(*i) += 2;
	}
	return (0);
}

int	make_right_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_out = R_HEREDOC;
	if (input_split[(*i) + 1])
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(input_split[*i + 1]);
		cmd->fd_file = open(input_split[*i + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (cmd->fd_file < 0)
		{
			printf("cannot open file : %s\n", cmd->outfile);
			free_cmd(cmd);
			return (1);
		}
		close(cmd->fd_file);
	}
	(*i) += 2;
	return (0);
}

int	make_left_heredoc(t_cmds *cmd, char **input_split, int *i)
{
	cmd->redir_in = L_HEREDOC;
	if (input_split[(*i) + 1])
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(input_split[(*i) + 1]);
	}
	(*i) += 2;
	return (0);
}

void	ft_increment(int *i, int *n)
{
	(*n)++;
	(*i)++;
}

int	make_args(t_cmds *cmd, char **input_split, int *i, int *n)
{
	char	*tmp;

	if ((ft_strncmp(cmd->cmd, "echo", 4) == 0 && cmd->args[0] != '\0')
		|| cmd->file_name[0] != NULL)
	{
		cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
		ft_increment(i, n);
		return (0);
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0
		|| ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		cmd->file_name[(*n)] = ft_strdup(input_split[(*i)]);
		ft_increment(i, n);
		return (0);
	}
	if (cmd->args[0] != '\0')
		tmp = ft_strjoin(cmd->args, " ");
	else
		tmp = ft_calloc(sizeof(char), 1);
	free(cmd->args);
	cmd->args = ft_strjoin_free(tmp, input_split[(*i)]);
	(*i)++;
	return (0);
}

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

int	make_args_next(t_cmds *cmd, char **input_split, int *i, int *n)
{
	int	error;

	error = 0;
	if (input_split[*i] && ft_strcmp(input_split[(*i)], "<<") == 0)
		error = make_left_heredoc(cmd, input_split, i);
	else if (input_split[*i] && ft_strncmp(input_split[(*i)], "-", 1) == 0
		&& cmd->cmd[0] != '\0')
		error = make_args(cmd, input_split, i, n);
	else if (input_split[*i] && cmd->cmd[0] == '\0')
		error = make_cmd(cmd, input_split, i);
	else if (input_split[*i])
		error = make_file(cmd, input_split, i, n);
	else
		(*i)++;
	return (error);
}

t_cmds	*make_arg(char **input_split, int j, t_cmds *cmd)
{
	int		i;
	int		n;
	int		error;

	i = 0;
	n = 0;
	error = 0;
	while (i < j)
	{
		if (error != 0)
			return (NULL);
		if (input_split[i] && ft_strcmp(input_split[i], "<") == 0)
			error = make_left_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">") == 0)
			error = make_right_redir(cmd, input_split, &i);
		else if (input_split[i] && ft_strcmp(input_split[i], ">>") == 0)
			error = make_right_heredoc(cmd, input_split, &i);
		else
			error = make_args_next(cmd, input_split, &i, &n);
	}
	return (cmd);
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

void	ft_create_heredoc_in(char *str, int i)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = ft_strjoin_free_choice(".heredoc", ft_itoa(i), 2);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(name);
	tmp = get_next_line(0);
	name = ft_strjoin(str, "\n");
	while ((tmp) && (ft_strncmp(name, tmp, ft_strlen(name))) != 0)
	{
		ft_putstr_fd(tmp, fd);
		free(tmp);
		tmp = get_next_line(0);
	}
	if (tmp)
		free(tmp);
	free(name);
	close(fd);
}

void	ft_create_heredoc_out(char *str, int i)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = ft_strjoin_free_choice(".heredoc", ft_itoa(i), 2);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(name);
	tmp = get_next_line(0);
	name = ft_strjoin(str, "\n");
	while ((ft_strncmp(name, tmp, ft_strlen(name))) != 0)
	{
		ft_putstr_fd(tmp, fd);
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	free(name);
	close(fd);
}

int	ft_left_redir(char **input_split, int *i)
{
	int	output;

	output = open(input_split[(*i) + 1], O_RDONLY);
	if (output != -1)
		close (output);
	else
		return (1);
	(*i)++;
	return (0);
}

char	**ft_make_input_split(char *input, char **envp)
{
	char	**input_split;

	input_split = ft_split_input(input, ' ');
	input_split = vars(envp, input_split);
	return (input_split);
}

void	ft_make_heredoc_in(t_cmds *cmd, char **input_split, int *i)
{
	char	*tmp_in;

	if (cmd->heredoc_in[0] != '\0')
		unlink(cmd->heredoc_in);
	ft_create_heredoc_in(input_split[(*i) + 1], (*i));
	free(cmd->heredoc_in);
	tmp_in = ft_strjoin_free_choice(".heredoc", ft_itoa((*i)), 2);
	cmd->heredoc_in = tmp_in;
	(*i)++;
}

void	ft_free_some_shit(char **input_split, t_cmds *cmd)
{
	ft_free_split(input_split);
	free_cmd(cmd);
}

void	ft_free_some_shit4(char **input_split, t_cmds *cmd)
{
	ft_free_split(input_split);
	free_cmd(cmd);
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

static void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 128 + sig;
		close(STDIN_FILENO);
	}
}

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

void	ft_free_some_shit_2(char **input_split, int j, char *input, t_cmds *cmd)
{
	ft_nfree_split(input_split, j);
	free(input);
	free_cmd(cmd);
}

void	ft_free_some_shit_3(char *input, char **cmd_split)
{
	free(input);
	ft_free_split(cmd_split);
}

int	ft_parse_input_next(char **cmd_split, t_cmds *cmd,
	char *input, char **envp)
{
	char	**input_split;
	int		j;
	int		i;

	i = 0;
	while (cmd)
	{
		j = 0;
		input_split = ft_split_input(cmd_split[i], ' ');
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
		i++;
		cmd = cmd->next;
	}
	ft_free_some_shit_3(input, cmd_split);
	return (0);
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
			ft_free_some_shit4(input_split, cmd);
			return (1);
		}
	}
	return (0);
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
			return (NULL);
		i++;
	}
	ft_free_split(input_split);
	return (save);
}

void	ft_fork(t_cmds *cmd, char *input, char **envp)
{
	free_cmd(cmd);
	signal(SIGINT, sig_handler_child);
	cmd = ft_make_here_doc(input, envp);
	free_cmd(cmd);
	free(input);
	ft_free_split(envp);
	exit(g_exit_code);
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
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
		ft_fork(cmd, input, envp);
	else
	{
		free_cmd(cmd);
		cmd = ft_get_heredoc_in(input, envp);
		waitpid(pid, NULL, 0);
	}
	cmd_split = ft_split_input(input, '|');
	if (ft_parse_input_next(cmd_split, cmd, input, envp) == 1)
		return (NULL);
	return (cmd);
}
