# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/16 15:42:13 by ggrybova          #+#    #+#              #
#    Updated: 2017/08/16 17:08:46 by ggrybova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = main.c fill_data.c create_labyrinth.c draw.c hook.c
INC = -I wolf3d.h -I minilibx_macos/mlx.h

OBJ = $(SRC:.c=.o)

LIBOBJ = make -C libft/

CFLAGS = -c -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework AppKit

LIBINC = -L./libft -lft minilibx_macos/libmlx.a

LIB = libft/libft.a

all: $(NAME)

obj: $(OBJ)

$(NAME) : $(LIB) $(OBJ)
	gcc $(OBJ) $(LIBINC) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) -o $@ $<

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

$(LIB):
	make -j4 -C libft/ all
