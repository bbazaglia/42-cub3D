# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 10:58:08 by bbazagli          #+#    #+#              #
#    Updated: 2024/07/05 18:26:17 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

# VPATH = 

INCLUDE = -I./include -I ./MLX42/include -I ./LIBFT/include

LIBFT = ./LIBFT/libft.a

SRC = main.c \
	parse.c \
	validate_scene.c \
	validate_map.c \
	utils.c \
	init.c \
	game_over.c

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft libmlx $(NAME)

$(NAME): libft $(SRC_OBJ) 
	@$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) -o $(NAME) 
	@echo "Compilation completed: $@"

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

libft:
	@make -C ./LIBFT

$(OBJ)/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<\n)"

clean: 
	@make -C ./LIBFT clean --silent
	@rm -rf $(OBJ)
	@rm -rf ./MLX42/build
	@echo "objects removed" 

fclean: clean
	@make -C ./LIBFT fclean --silent 
	@rm -f $(NAME) 
	@echo "executable removed"

re: fclean all

.PHONY: all clean fclean re libft bonus
