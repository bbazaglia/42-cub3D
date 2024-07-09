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

VPATH = src

INCLUDE = -I./include -I ./MLX42/include -I ./LIBFT/include

LIBFT = ./LIBFT/libft.a

SRC = main.c \
	parse.c \
	validate_scene.c \
	validate_map.c \
	utils.c \
	init.c \
	load_images.c \
	hooks.c \
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

build_mlx:
ifeq (,$(wildcard ./lib/MLX42/build/libmlx42.a))
	git clone https://github.com/codam-coding-college/MLX42.git && \
	cd MLX42 && \
	sed -i 's/cmake_minimum_required (VERSION 3.18.0)/cmake_minimum_required (VERSION 3.16.0)/g' CMakeLists.txt && \
	if ! cmake -B build; then \
		echo "Failed to configure MLX42"; \
	else \
		cmake --build build -j4; \
	fi
endif

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
