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

CFLAGS = -Wall -Wextra -Werror -g3

LIBS = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

VPATH = src

INCLUDE = -I./include -I./MLX42/include -I./LIBFT/include

LIBFT = ./LIBFT/libft.a

SRC = main.c \
      parse.c \
      validate_scene.c \
      validate_map.c \
      utils.c \
      init.c \
      load_images.c \
      hooks.c \
      game_over.c \
	  render.c \
	  math.c \
	  bresenham.c \

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft $(NAME)

$(NAME): $(SRC_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "Compilation completed: $@"

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

libft:
	@make -C ./LIBFT

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppress_mlx.sup ./cub3D ./maps/validmap.cub

$(OBJ)/%.o: %.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<)\n"

clean:
	@make -C ./LIBFT clean --silent
	@rm -rf $(OBJ)
	@echo "Objects removed"

cleanmlx:
	@rm -rf ./MLX42/build

fclean: clean
	@make -C ./LIBFT fclean --silent
	@rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

.PHONY: all clean fclean re libft libmlx
