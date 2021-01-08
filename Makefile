# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wspectra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 21:44:41 by wspectra          #+#    #+#              #
#    Updated: 2020/12/19 21:44:43 by wspectra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= cub3d.c read_file.c\
parsing.c check_resolution_validity.c check_colors_validity.c\
			check_path_validity.c check_map_validity.c check_cell.c\

#cub3d_map.c cmake_cub.c print_map.c

OBJS		=  $(SRCS:.c=.o)

LIBFT		= ./libft/libft.a

MLX			= ./mlx/libmlx.dylib

INCL		= cub3d.h

CC			= gcc

RM			= rm -f

FLAGS		= -Wall -Wextra -Werror

FLAGS_MLX	= -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
		$(CC) -L./mlx $(FLAGS_MLX) -lmlx -L./libft/ -lft $(OBJS) -o $(NAME)

$(LIBFT):
		make -C ./libft/

$(MLX):
		make -C ./mlx/
		cp ./mlx/libmlx.dylib ./

%.o: %.c $(INCL)
		 $(CC) $(FLAGS) -I ./mlx.h -c $< -o $@

clean:
		$(RM) $(OBJS)
		make clean -C ./libft/
		make clean -C ./mlx/

fclean: clean
		$(RM) $(NAME)
		$(RM) libmlx.dylib
		$(RM) ./mlx/libmlx.dylib
		make fclean -C ./libft/

re:		fclean all

.PHONY:
		all, clean, fclean, re