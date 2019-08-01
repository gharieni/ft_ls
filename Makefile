# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 21:45:33 by ghamelek          #+#    #+#              #
#    Updated: 2019/01/16 00:17:32 by ghamelek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = ft_ls
SRC_PATH = src
CPPFLAGS = -Iinclude
LDFLAGS = -Llibft
LDLIBS = -lft
CC = gcc
INC = includes
CFLAGS = -Wall -Werror -Wextra
SRC_NAME = main.c\
	ls_l.c\
	argum.c\
	print.c\
	trees.c\
	list.c\
	tools.c\
	free.c\
	free2.c
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ= $(SRC:.c=.o)

all : $(NAME)
$(NAME): $(OBJ)
	@echo "\033[92mCOMPILE\033[0m"
	make -C libft/
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS)  -I $(INC) -o $(NAME) $(LDLIBS)
	@echo "\033[92mSUCCES COMPILE\033[0m"
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(INC) -o $@ -c $<

clean:
	@echo "\033[92mCLEAN\033[0m"
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	@echo "\033[92mFCLEAN\033[0m"
	make -C libft/ fclean
	rm -fv $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
