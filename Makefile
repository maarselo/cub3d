# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#              #
#    Updated: 2026/01/27 21:06:08 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#main paths
DIR_SRC = src
DIR_OBJS = objs
DIR_DEPS = deps
DIR_LIBFT = libs/libft
DIR_MLX = libs/mlx/build

#sources paths
DIR_VALIDATOR = validator
DIR_VALIDATOR_ARGUMENTS = arguments
DIR_VALIDATOR_CONFIG = config
DIR_VALIDATOR_MAP = map
DIR_PARSER = parser
DIR_GAME = game
DIR_ERROR = error
DIR_UTILS = utils
DIR_FREE = free


SRC_VALIDATOR = validator.c \
			$(DIR_VALIDATOR_ARGUMENTS)/arguments.c \
			$(DIR_VALIDATOR_CONFIG)/config.c $(DIR_VALIDATOR_CONFIG)/config_helpers.c $(DIR_VALIDATOR_CONFIG)/config_validator.c $(DIR_VALIDATOR_CONFIG)/config_validator_helpers.c $(DIR_VALIDATOR_CONFIG)/config_content.c \
			$(DIR_VALIDATOR_MAP)/map.c $(DIR_VALIDATOR_MAP)/map_content.c 
SRC_PARSER = parser.c data.c mlx.c player.c map.c textures.c colors.c 
SRC_GAME = game.c
SRC_ERROR = init_error.c set_error.c strerror.c handler_error.c   
SRC_UTILS = file.c file_utils.c
SRC_FREE = free_file_content.c free_content_assigned.c free_split.c free_data.c


#diferent folder with files
FILES_VALIDATOR = $(addprefix $(DIR_VALIDATOR)/, $(SRC_VALIDATOR))
FILES_PARSER = $(addprefix $(DIR_PARSER)/, $(SRC_PARSER))
FILES_GAME = $(addprefix $(DIR_GAME)/, $(SRC_GAME))
FILES_ERROR = $(addprefix $(DIR_ERROR)/, $(SRC_ERROR))
FILES_UTILS = $(addprefix $(DIR_UTILS)/, $(SRC_UTILS))
FILES_FREE = $(addprefix $(DIR_FREE)/, $(SRC_FREE))


#all files
FILES = main.c $(FILES_VALIDATOR) $(FILES_PARSER) $(FILES_GAME) \
	 $(FILES_ERROR) $(FILES_UTILS) $(FILES_FREE)

SRCS = $(addprefix $(DIR_SRC)/,$(FILES))

OBJS = $(addprefix $(DIR_OBJS)/, $(FILES:.c=.o))

DEPS = $(addprefix $(DIR_DEPS)/, $(FILES:.c=.d))

#libs to use
LIBFT = $(DIR_LIBFT)/libft.a
MLX = $(DIR_MLX)/libmlx42.a
#headers of the libs
HEADER_LIBTF = $(DIR_LIBFT)/include
HEADER_MLX = ./libs/mlx/include/MLX42

#all flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS_MLX = -ldl -lglfw -pthread -lm
CFLAGS_DEPENDECIES = -MMD -MP
CFLAGS_INCLUDE = -I$(HEADER_LIBTF) \
				-I$(HEADER_MLX) \
				-Iinclude	\
				-Isrc

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
	$(RM) $(LIBFT) $(DIR_MLX) $(NAME)

re: fclean all

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re

valgrind: CFLAGS = -Wall -Werror -Wextra
valgrind: re $(NAME)
	valgrind --leak-check=full ./$(word 2, $^)

.PHONY: all clean fclean re debug valgrind

-include $(DEPS)