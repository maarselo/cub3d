# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#              #
#    Updated: 2026/01/10 23:39:56 by mvillavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#main paths
DIR_SRC = src
DIR_OBJS = objs
DIR_DEPS = deps
DIR_LIBFT = libs/libft

#sources paths
DIR_VALIDATOR = validator
DIR_ERROR = error
DIR_UTILS = utils


SRC_VALIDATOR = validator.c arguments.c map.c
SRC_ERROR = init_error.c set_error.c strerror.c handler_error.c   
SRC_UTILS = file.c file_utils.c


#diferent folder with files
FILES_VALIDATOR = $(addprefix $(DIR_VALIDATOR)/, $(SRC_VALIDATOR))
FILES_ERROR = $(addprefix $(DIR_ERROR)/, $(SRC_ERROR))
FILES_UTILS = $(addprefix $(DIR_UTILS)/, $(SRC_UTILS))


#all files
FILES = main.c $(FILES_VALIDATOR) $(FILES_ERROR) $(FILES_UTILS)

SRCS = $(addprefix $(DIR_SRC)/,$(FILES))

OBJS = $(addprefix $(DIR_OBJS)/, $(FILES:.c=.o))

DEPS = $(addprefix $(DIR_DEPS)/, $(FILES:.c=.d))

#libs to use
LIBFT = $(DIR_LIBFT)/libft.a
MLX = libs/mlx/build/libmlx42.a
#headers of the libs
HEADER_LIBTF = $(DIR_LIBFT)/include
HEADER_MLX = ./libs/mlx/include/MLX42

#all flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS_MLX = -ldl -lglfw -pthread -lm
CFLAGS_DEPENDECIES = -MMD -MP
CFLAGS_INCLUDE = -Iinclude -I$(HEADER_LIBTF) -I$(HEADER_MLX)
CFLAGS_DEBUG = -fsanitize=address,leak

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(CFLAGS_MLX) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	make -C $(DIR_LIBFT)
$(MLX):
	cd libs/mlx && cmake -B build && cmake --build build -j4 && cd -
	
$(DIR_OBJS)/%.o: $(DIR_SRC)/%.c
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DIR_DEPS)/$*.d)
	$(CC) $(CFLAGS) $(CFLAGS_INCLUDE) $(CFLAGS_DEPENDECIES) -c $< -o $@ -MF $(DIR_DEPS)/$*.d

clean: 
	$(RM) $(DIR_OBJS) $(DIR_DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re

valgrind: CFLAGS = -Wall -Werror -Wextra
valgrind: re $(NAME)
	valgrind --leak-check=full ./$(word 2, $^)

.PHONY: all clean fclean re debug valgrind

-include $(DEPS)