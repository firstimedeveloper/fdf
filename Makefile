# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 15:47:16 by juhan             #+#    #+#              #
#    Updated: 2022/04/15 16:15:16 by juhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Werror -Wextra
LIBX_PATH=./minilibx
LIBX_FLAG=-framework OpenGl -framework Appkit
LIB_PATH=libft
SRC_PATH=./src/
BUILD_PATH=./build/

FILE_NAMES=fdf get_next_line get_next_line_utils handle_key handle_exit projection init draw draw_line rotate_util
SRC=$(addprefix $(SRC_PATH), $(addsuffix .c, $(FILE_NAMES)))
OBJ=$(SRC:$(SRC_PATH)%.c=$(BUILD_PATH)%.o)
DEP=$(OBJ:.o=.d)

NAME=fdf

all: $(NAME)

$(NAME): $(OBJ) $(LIB_PATH)/libft.a $(LIBX_PATH)/libmlx.a
	$(CC) $(LIBX_PATH)/libmlx.a $(LIBX_FLAG) $(LIB_PATH)/libft.a $(OBJ) -o $@

$(LIB_PATH)/libft.a:
	make -C libft

$(LIBX_PATH)/libmlx.a:
	make -C $(LIBX_PATH)

$(BUILD_PATH)%.o : $(SRC_PATH)%.c
	$(CC) -MMD -I. -c $< -o $@

-include $(DEP)

clean :
	$(RM) $(OBJ) $(DEP)
	@make clean -C $(LIBX_PATH)
	@make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME) libft/libft.a
	$(RM) $(NAME) $(LIBX_PATH)/libmlx.a

re : fclean all

.PHONY :
	all clean fclean re

