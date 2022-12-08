# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 13:39:14 by jlarrieu          #+#    #+#              #
#    Updated: 2022/12/06 18:31:16 by pdubacqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_isalpha.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isdigit.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_substr.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_strchr.c \
		ft_str_index_chr.c \
		ft_strncmp.c \
		ft_strtrim.c \
		ft_strjoin.c \
		ft_strnstr.c \
		ft_split.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strmapi.c \
		ft_striteri.c \
		get_next_line.c \
		ft_strjoin_free.c

BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ = ${SRC:.c=.o}
BOBJ = ${BONUS:.c=.o}
CC = gcc
AR = ar -rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = libft.a

all: ${NAME}

bonus: ${OBJ} ${BOBJ}
		${AR} ${NAME} ${OBJ} ${BOBJ}

%.o: %.c
		$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
		${AR} $@ $^

clean:
		${RM} ${OBJ} ${BOBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all bonus

.PHONY : all clean fclean re bonus
