SRCS			= $(wildcard *.c)
OBJS			= $(SRCS:.c=.o)
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3  -fsanitize=thread

NAME = philo

#-Ipathfinkyanin_headerst
#-Lpath_finkayna_lib -lsmiyadyallib
all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:clean
		$(RM) $(NAME)

re:		fclean all
