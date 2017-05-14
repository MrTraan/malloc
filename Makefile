# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/30 14:36:55 by ngrasset          #+#    #+#              #
#    Updated: 2017/05/14 18:58:37 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK_NAME = libft_malloc.so

SRC = ./src/block_creation.c \
./src/block_deletion.c \
./src/heap_creation.c \
./src/malloc_safe.c \
./src/malloc_unsafe.c \
./src/dump_memory.c \
./src/block_helpers.c \
./src/strings.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wextra -Wall -Werror

INC = -I include

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -shared -o $(NAME) $(OBJ) $(INC)
	ln -fs $(NAME) $(LINK_NAME)

%.o: %.c
	gcc -c $(CFLAGS) $(INC) $(LIBFT_INC) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LINK_NAME)

re: fclean all

test: $(OBJ)
	gcc -c $(INC) $(LIBFT_INC) tests/main.c -o tests/main.o
	gcc -g -fsanitize=address -o test_malloc $(INC) $(OBJ) tests/main.o

.PHONY: all clean fclean re
