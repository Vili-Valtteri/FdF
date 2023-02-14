# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 18:25:17 by raho              #+#    #+#              #
#    Updated: 2022/04/21 16:43:39 by vlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
LIB = libft/libft.a
DSYM = fdf.dSYM
INCLUDE = libft/
LIBMLX = libmlx.dylib
CFLAGS = -I $(INCLUDE) -Wall -Wextra -Werror
SRCS = main.c pixel_placement.c save_coordinates.c free_all.c copy_file.c \
inputs.c handle_file.c open_window.c fill_image.c math_functions.c \
triangle_functions.c brez_functions.c error_check.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(LIBMLX) $(OBJS)
	$(CC) -I $(INCLUDE) $(LIB) $(LIBMLX) $(OBJS) -o $(NAME) -O2 $(CFLAGS)

$(LIB):
	make -C libft

$(LIBMLX):
	make -C  minilibx
	mv minilibx/libmlx.dylib libmlx.dylib

clean:
	make -C libft clean
	make -C minilibx clean
	rm -rf $(DSYM)
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re
