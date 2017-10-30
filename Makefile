# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelek <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 16:54:30 by gmelek            #+#    #+#              #
#    Updated: 2017/10/30 17:34:44 by gmelek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CCLIB = -Llibft -lft
CCFLAGS = -Wall -Werror -Wextra
RCDIR = src
OBJDIR = obj
INCDIR = includes libft

SRC = 	main.c\
		ls_l.c\
		libft/*.c

RCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS = $(addprefix -I , $(INCDIR))

all: $(NAME)
	$(NAME): build $(OBJS)
	@make -C libft
	@gcc $(CCLIB) -o $(NAME) $(OBJS)
build:
	@mkdir -p $(OBJDIR)
clean:
	@make -C libft clean
	@rm -f $(OBJS)
	fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	re: fclean all

dev : all
	@./$(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
