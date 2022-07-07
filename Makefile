# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 19:38:36 by mdkhissi          #+#    #+#              #
#    Updated: 2021/11/04 16:07:58 by mdkhissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = srcs/main.c srcs/pipex.c srcs/utils.c srcs/ft_split.c srcs/strutils.c srcs/cmd.c

OBJS = ${SRCS:.c=.o}

HEADER = includes

CC = clang

CFLAGS = -Wall -Wextra -Werror

RM = rm -f


.c.o:
	${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

all : ${NAME}
$(NAME): ${OBJS}
	${CC} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
