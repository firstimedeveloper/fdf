CC = gcc -Wall -Werror -Wextra
LIBX_PATH=minilibx_opengl_20191021
LIBX_FLAG=-framework OpenGl -framework Appkit
LIB_PATH=libft

FILE_NAMES =fdf get_next_line get_next_line_utils
SRCS=$(addsuffix .c, $(FILE_NAMES))
OBJS=$(SRCS:.c=.o)

NAME=fdf

$(NAME): $(OBJS) $(LIB_PATH)/libft.a $(LIBX_PATH)/libmlx.a
	$(CC) $(LIBX_PATH)/libmlx.a $(LIBX_FLAG) $(LIB_PATH)/libft.a $(OBJS) -o $@

$(LIB_PATH)/libft.a:
	make -C libft

$(LIBX_PATH)/libmlx.a:
	make -C $(LIBX_PATH)

%.o : %.c
	$(CC) -D BUFFER_SIZE=30 -c $?

clean :
	$(RM) $(OBJS)
	@make clean -C $(LIBX_PATH)
	@make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME) libft/libft.a
	$(RM) $(NAME) $(LIBX_PATH)/libmlx.a

re : fclean all

.PHONY :
	all clean fclean re

