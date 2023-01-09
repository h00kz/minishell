#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structs.h"
# include "lists.h"
# include "builtins.h"
# include <sys/wait.h>

extern int	g_exit_code;

enum	e_redir
{
	L_REDIR = 1,
	R_REDIR = 2,
	L_HEREDOC = 3,
	R_HEREDOC = 4,
	PIPE = 5,
};

enum	e_parsing
{
	FILES = 0,
	INFILE = 1,
	CMD = 2,
	ARGS_OR_FILE = 3,
	FILES_OR_CMD = 4,
};

/********************************parsing***************************************/

t_cmds	*make_arg(char **input_split, int j, t_cmds *cmd);
t_cmds	*parse_input(char *input, char **envp);
char	*translate_env_vars(char *input, char **envp);

/*********************************utils****************************************/

t_cmds	*ft_lstnew_node(char **envp);
t_cmds	*lstnew_cmd(char **input_split, char **envp);
char	**ft_cpy_envp(char **envp);
void	free_cmd(t_cmds *cmd);

/*********************************split****************************************/

char	**ft_split_input(char const *s, char c);
void	ft_free_split(char **strs);
void	ft_nfree_split(char **strs, int n);

#endif
