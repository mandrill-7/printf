# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchanal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/04 06:29:39 by fchanal           #+#    #+#              #
#    Updated: 2017/06/10 15:53:40 by fchanal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################
###                  Settings                 ###
#################################################

NAME = libftprintf.a
CC = clang
FLAGS = -Wall -Wextra -Werror
SRC_PATH = ./srcs/
INC_PATH = -I./includes/

#################################################
###                  Colors                   ###
#################################################

COL_BLACK  = \033[1;30m
COL_RED    = \033[1;31m
COL_GREEN  = \033[1;32m
COL_YELLOW = \033[1;33m
COL_BLUE   = \033[1;34m
COL_PURPLE = \033[1;35m
COL_WHITE  = \033[1;37m

#################################################
###                 Sources                   ###
#################################################

SRC =\
	\
	ft_vdprintf.c \
	ft_vprintf.c \
	ft_printf.c \
	ft_dprintf.c \
	pf_color.c \
	pf_buffering.c \
	pf_utilities.c \
	pf_unicode_handler.c \
	pf_get_attr.c \
	pf_numb_conv_tools.c \
	pf_casting.c \
	\
	pf_specifier/pf_convert_m.c \
	pf_specifier/pf_convert_big_m.c \
	pf_specifier/pf_convert_b.c \
	pf_specifier/pf_convert_c.c \
	pf_specifier/pf_convert_big_c.c \
	pf_specifier/pf_convert_d.c \
	pf_specifier/pf_convert_o.c \
	pf_specifier/pf_convert_p.c \
	pf_specifier/pf_convert_s.c \
	pf_specifier/pf_convert_big_s.c \
	pf_specifier/pf_convert_u.c \
	pf_specifier/pf_convert_v.c \
	pf_specifier/pf_convert_x.c \
	pf_specifier/pf_convert_y.c \
	pf_specifier/pf_convert_big_y.c \
	pf_specifier/pf_convert_n.c \
	pf_specifier/pf_convert_w.c \
	pf_specifier/pf_convert_big_w.c \
	pf_specifier/float/pf_convert_f.c \
	pf_specifier/float/pf_float_engine.c \
	pf_specifier/float/pf_float_integer_part.c \
	\
	pf_mini_libft/ft_dexp.c \
	pf_mini_libft/ft_get_dint_part.c \
	pf_mini_libft/ft_memcpy.c \
	pf_mini_libft/ft_memcmp.c \
	pf_mini_libft/ft_memset.c \
	pf_mini_libft/ft_strchr.c \
	pf_mini_libft/ft_strchr_zero.c \
	pf_mini_libft/ft_strlen.c \
	pf_mini_libft/ft_strnlen.c \
	pf_mini_libft/ft_get_nbr.c \
	pf_mini_libft/ft_isdigit.c \
	pf_mini_libft/ft_isprint.c

#################################################
###                   Format                  ###
#################################################

SRCS = $(addprefix $(SRC_PATH), $(SRC))
O = $(notdir $(SRC))
OB = $(basename $(O))
OBJ = $(addsuffix .o ,$(OB))

#################################################
###                   Rules                   ###
#################################################

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ): $(SRCS)
	$(CC) -c $(FLAGS) $(INC_PATH) $(SRCS)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
