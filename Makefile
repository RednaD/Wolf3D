# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/08 14:46:44 by iporsenn          #+#    #+#              #
#    Updated: 2018/11/01 16:48:01 by arusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_PATH = src/
SRC_NAME =	born_to_norm.c		\
			check_map.c			\
			draw.c				\
			init_struct.c		\
			input.c				\
			key_hook.c			\
			main.c				\
			mini_map.c			\
			raycasting_loop.c

SRC =  $(addprefix $(SRC_PATH), $(SRC_NAME))

INCLUDE_PATH = includes/
INCLUDE_NAME = wolf_3d.h
INCLUDE = $(addprefix $(INCLUDE_PATH), $(INCLUDE_NAME))

OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(SRC_NAME:.c=.o))

HEADER_PATH = minilibx_macos/
HEADER_NAME = libmlx.a
HEADER = $(addprefix $(HEADER_PATH), $(HEADER_NAME))

FLAGS = -Wall -Werror -Wextra
FLAGS_LIBX = -lmlx -framework OpenGL -framework AppKit -lpthread -D_REENTRANT

.PHONY: all, build, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@make -C libft
	@gcc $(FLAGS) $(FLAGS_LIBX) $(SRC) ./libft/libft.a $(HEADER) -o $(NAME)
	@echo "\033[32mExe built\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -o $@ -c $<

build :
	@gcc $(FLAGS) $(FLAGS_LIBX) $(SRC) ./libft/libft.a $(HEADER) -o $(NAME)
	@echo "\033[32mExe built\033[0m"

clean:
	@make clean -C libft
	@rm -rf $(OBJ_PATH)
	@echo "\033[31m.o cleaned\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[31mAll cleaned\033[0m"

re: fclean all
