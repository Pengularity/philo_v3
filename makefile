NAME = philo

INCLUDE = ./include/

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE) -MMD

SRCS = src/main.c \
			src/monitor.c \
			src/mutex.c \
			src/parse_init.c \
			src/print_time.c \
			src/routine.c \
			src/utils.c \
			

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -g
	@toilet -f pagga.tlf -F border "philo compiled"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re