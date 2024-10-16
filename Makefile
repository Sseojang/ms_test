# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 09:48:53 by seojang           #+#    #+#              #
#    Updated: 2024/10/16 16:25:46 by seojang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.DEFAULT_GOAL := all

CC = cc
RM = rm -rf

SRC = main.c \
	ft_tokenizer.c \
	ft_export.c \
	ft_qoute.c \
	ft_split.c \
	ft_split_utils.c \
	ft_libft.c \
	ft_lst_util.c \
	ft_paser.c \
	ft_paser_util_pipe.c \
	ft_paser_util_redir.c \
	ft_paser_util_exe.c \
	ft_paser_utils.c \
	ft_utils.c

HEADER = ms_test.h

OBJ_S = $(SRC_S:.c=.o) 

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

NAME = minishell

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@

%.o : %.c
	$(CC) -c $< -o $@
	
clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re
