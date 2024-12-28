NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS	=	main.c t_utils.c init.c thread.c utils.c

OBJS	= $(SRCS:.c=.o)

HEADER	= philosophers.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean