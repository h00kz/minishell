SRC					= src/main.c \
					  src/list_envp/process_envp.c \
					  src/utils/list_utils.c \
					  src/utils/list_utils_next.c \
					  src/split/split_for_input.c \
					  src/split/split_utils.c \
					  src/builtins/echo.c \
					  src/builtins/cd.c \
					  src/builtins/exit.c \
					  src/builtins/export.c \
					  src/builtins/export_utils.c \
					  src/builtins/pwd.c \
					  src/builtins/unset.c \
					  src/builtins/env.c \
					  src/parsing/arguments.c \
					  src/parsing/parse_input.c \
					  src/parsing/env_interpretation.c \
					  src/parsing/env_vars.c \
					  src/parsing/exec/redir_check.c \
					  src/parsing/exec/redir_utils.c \
					  src/parsing/exec/heredocs.c \
					  src/parsing/exec/heredoc_fork.c \
					  src/parsing/exec/heredocs_utils.c \
					  src/parsing/exec/r_utils.c \
					  src/parsing/exec/free_some_s.c \
					  src/execve/execve.c \
					  src/execve/fork.c \
					  src/execve/fork_utils.c

LIBFT				= libft/
CFLAGS				=  -g -lreadline -Werror -Wextra -Wall
NAME				= minishell
LIB					= libft/libft.a
INCLUDE				= inc/

blink				= \033[5m
NC					= \033[0m
bold				:= $(shell tput bold)
blue				:= $(shell tput setaf 4)
green				:= $(shell tput setaf 2)
red					:= $(shell tput setaf 1)
sgr0				:= $(shell tput sgr0)

all: $(NAME)

$(NAME):
	@make -sC $(LIBFT) all
	@gcc $(SRC) -o $(NAME) $(LIB) $(CFLAGS) -I $(INCLUDE) 
	@printf "[$(green)✔$(sgr0)] $(bold)$(green)Compiling Minishell finished!$(sgr0)\n"

clean:
	@make -sC $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -sC $(LIBFT) fclean
	@printf "[$(red)✔$(sgr0)] $(bold)$(blue)Removing Minishell binary and libft objs done.$(sgr0)\n"

re: fclean all

.PHONY: all clean fclean re