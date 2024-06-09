# NAME = philo
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# SRCS = main.c ft_atol.c parsing.c
# OBJS = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS)
#     $(CC) $(CFLAGS) -o

# clean:
#     rm -f $(OBJS)

# fclean: clean
#     rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
SRCS			= main.c ft_atol.c parsing.c\

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME = philo

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(NAME)

fclean:
		$(RM) $(NAME)
		$(RM) server_bonus client_bonus

re:		fclean $(NAME)
