# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 19:38:36 by mdkhissi          #+#    #+#              #
#    Updated: 2022/07/09 00:02:45 by mdkhissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

# ----------- COMPILER FLAGS -------
CC			= clang
CFLAGS		= -Wall -Wextra -Werror

# ----------- INCLUDE --------------
HEADER		= includes
INCLUDE		= -I $(HEADER)

# ----------- FILES ----------------
SRC			= srcs
OBJ			= obj
SRCS		= $(SRC)/main.c $(SRC)/pipex.c $(SRC)/utils.c $(SRC)/ft_split.c $(SRC)/strutils.c $(SRC)/cmd.c
OBJS		= $(patsubst $(SRC)/%.c, $(OBJ)/%.o,$(SRCS))

# ----------- COLORS ---------------
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
PURPLE		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
EOC			= \033[0;0m

# ----------- RULES ----------------
all			: ${NAME}
$(NAME)		: ${OBJS}
	@echo -e "$(RED) =========> Compiling object files.............DONE √\n"
	@echo -e "$(WHITE)"
		${CC} -o ${NAME} ${OBJS}
	@echo -e "$(RED) =========> Building push_swap.............DONE √\n"

$(OBJ)/%.o	: $(SRC)/%.c | $(OBJ) compiling
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ)		:
	@echo -e "$(PURPLE)"
		mkdir $@

compiling	:
	@echo -e "$(WHITE)"
	
clean:
	@echo -e "$(PURPLE)"
		-rm -rf ${OBJ}
	@echo -e "$(RED) =========> Deleting object files.............DONE √\n"

fclean: clean
	@echo -e "$(PURPLE)"
		-rm -f ${NAME}
	@echo -e "$(RED) =========> Deleting executable.............DONE √\n"

re:		fclean all

norm		:
	@echo -e "$(CYAN)"
		norminette $(SRC) $(HEADER)
	@echo -e "$(RED) =========> Checking the norminette.............DONE √\n"

.PHONY: all clean fclean re norm
