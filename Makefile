# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 16:35:42 by jlarrieu          #+#    #+#              #
#    Updated: 2022/11/30 16:22:10 by jlarrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC					= src/main.c \
					  src/envp/envp_process.c \
					  src/utils/gets.c \
					  src/utils/list_utils.c

LIBFT				= libft/
CFLAGS				=  -g #-Werror -Wextra -Wall
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