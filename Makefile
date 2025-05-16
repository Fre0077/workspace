NAME=webserv

HEADERS = \
headers/webserv.hpp

SRCS = \
srcs/main.cpp \
srcs/response.cpp \
srcs/init.cpp

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME) $(HEADERS)

$(NAME): $(SRCS)
	c++ $(CPPFLAGS) -o $(NAME) $(SRCS)

clean:

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re