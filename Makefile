NAME=webserv

SRCS = \
srcs/main.cpp

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME)

$(NAME): $(SRCS)
	c++ $(CPPFLAGS) -o $(NAME) $(SRCS)

clean:

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re