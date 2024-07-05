# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 10:58:08 by bbazagli          #+#    #+#              #
#    Updated: 2024/07/05 10:16:44 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 

# VPATH = 

INCLUDE = -I./include -I ./LIBFT/include

LIBFT = ./LIBFT/libft.a

SRC = main.c \
	parse.c \
	validate_scene.c \
	game_over.c

OBJ = obj

SRC_OBJ = $(SRC:%.c=$(OBJ)/%.o)

all: libft $(NAME)

$(NAME): libft $(SRC_OBJ) 
	@$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) -o $(NAME) 
	@echo "Compilation completed: $@"

libft:
	@make -C ./LIBFT

$(OBJ)/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<\n)"

clean: 
	@make -C ./LIBFT clean --silent
	@rm -rf $(OBJ)
	@echo "objects removed" 

fclean: clean
	@make -C ./LIBFT fclean --silent 
	@rm -f $(NAME) 
	@echo "executable removed"

re: fclean all

.PHONY: all clean fclean re libft bonus
