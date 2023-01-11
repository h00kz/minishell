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
# include "parsing.h"
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

#endif
