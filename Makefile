# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: string <string>                            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 10:58:08 by bbazagli          #+#    #+#              #
#    Updated: 2024/07/19 16:49:56 by string           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

LIBS = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

VPATH = src

INCLUDE = -I./include -I./MLX42/include -I./LIBFT/include

LIBFT = ./LIBFT/libft.a

SRC = main.c \
      parse.c \
      check_misconfiguration.c \
      validate_map.c \
      utils.c \
      init.c \
      load_images.c \
      hooks.c \
	  hooks_utils.c \
      game_over.c \
	  render.c \
	  minimap.c \
	  raycast.c \
	  raycast_math.c \
	  bresenham.c \
	  raycast_utils.c \

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

$(OBJ)/%.o: %.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<)\n"

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppress_mlx.sup ./cub3D ./maps/validmap.cub

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
