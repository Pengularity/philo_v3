NAME = philosophers

INCLUDE = ./include/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)

SRCS = src/main.c \
			src/monitor.c \
			src/mutex.c \
			src/parse_init.c \
			src/print_time.c \
			src/routine.c \
			src/utils.c \
			

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -g
	@toilet -f pagga.tlf -F border "philo compiled"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re