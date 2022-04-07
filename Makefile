NAME    = demineur

CC              = gcc
CFLAGS  = -Wall -Werror -Wextra -g -fsanitize=address

SRCS    =	main.c \
			utils.c \
			ingame.c


OBJS    = $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY:         all clean fclean re