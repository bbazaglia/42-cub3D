# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 10:32:51 by bbazagli          #+#    #+#              #
#    Updated: 2024/02/05 14:53:29 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_putchar_fd.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_split.c \
	ft_strlen.c \
	ft_substr.c \
	ft_strdup.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_strnstr.c \
	ft_strjoin.c \
	ft_atoi.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_calloc.c \
	ft_memcpy.c \
	ft_memcmp.c \
	ft_memchr.c \
	ft_memmove.c \
	ft_memset.c \
	ft_bzero.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strncmp.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstsize_bonus.c \
	ft_printf.c \
	ft_printf_utils.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_abs.c \
	ft_atol.c \
	get_next_line.c 

OBJ = $(addprefix ./src/, $(SRC:%.c=%.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADERS := -I ./include

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"
	@ar rcs $(NAME) $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
