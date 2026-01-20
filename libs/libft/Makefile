# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 16:51:09 by mvillavi          #+#    #+#              #
#    Updated: 2025/01/12 20:20:41 by mvillavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

DIR_INCLUDE = include
OBJ_DIR = obj
DEPS_DIR = deps

DIR_FILES_LIBFT = src/libft
DIR_FILES_GNL = src/gnl
DIR_FILES_PRINTF = src/ft_printf

HEADER_LIBFT = $(DIR_INCLUDE)/libft.h
HEADER_PRINTF = $(DIR_INCLUDE)/ft_printf.h

FILES_LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_isspace.c ft_ismetachar.c ft_isspace_str.c ft_toupper.c ft_tolower.c ft_atoi.c \
       ft_strlen.c ft_strlen_ignore.c ft_strlcpy.c ft_strlcat.c ft_itoa.c ft_strchr.c ft_strncmp.c \
       ft_strdup.c ft_strdup_ignore.c ft_strrchr.c ft_calloc.c ft_strjoin.c ft_memmove.c ft_memcmp.c \
       ft_strtrim.c ft_substr.c ft_strmapi.c ft_strnstr.c ft_putnbr_fd.c ft_get_lastc.c\
       ft_bzero.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_memset.c \
       ft_memchr.c ft_striteri.c ft_memcpy.c ft_split.c ft_realloc.c ft_multijoin.c
FILES_GNL = get_next_line.c
FILES_PRINTF = ft_printf.c ft_printf_utils.c

SRCS_LIBFT = $(addprefix $(DIR_FILES_LIBFT)/, $(FILES_LIBFT))
SRCS_GNL = $(addprefix $(DIR_FILES_GNL)/, $(FILES_GNL))
SRCS_PRINTF = $(addprefix $(DIR_FILES_PRINTF)/, $(FILES_PRINTF))

OBJS_LIBFT = $(addprefix $(OBJ_DIR)/, $(FILES_LIBFT:.c=.o))
OBJS_GNL = $(addprefix $(OBJ_DIR)/, $(FILES_GNL:.c=.o))
OBJS_PRINTF = $(addprefix $(OBJ_DIR)/, $(FILES_PRINTF:.c=.o))

DEPS = $(addprefix $(DEPS_DIR)/, $(FILES_LIBFT:.c=.d) $(FILES_GNL:.c=.d) $(FILES_PRINTF:.c=.d))

CC = cc
CC_LIB = ar -rcs
CFLAGS = -Wall -Werror -Wextra -Iinclude -MMD -MP
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_PRINTF) Makefile
	$(CC_LIB) $(NAME) $(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_PRINTF)

$(OBJ_DIR)/%.o: $(DIR_FILES_LIBFT)/%.c | $(OBJ_DIR) $(DEPS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)/$*.d
$(OBJ_DIR)/%.o: $(DIR_FILES_GNL)/%.c | $(OBJ_DIR) $(DEPS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)/$*.d
$(OBJ_DIR)/%.o: $(DIR_FILES_PRINTF)/%.c | $(OBJ_DIR) $(DEPS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)/$*.d

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

clean :
	$(RM) $(OBJ_DIR) $(DEPS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
