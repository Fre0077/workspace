NAME=webserv

HEADERS = \
headers/colours.hpp \
headers/Config.hpp \
headers/Extern.hpp \
headers/Server.hpp \
headers/webserv.hpp

SRCS = \
srcs/Config.cpp \
srcs/Extern.cpp \
srcs/init.cpp \
srcs/main.cpp \
srcs/response.cpp

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME) $(HEADERS)

$(NAME): $(SRCS)
	c++ $(CPPFLAGS) -o $(NAME) $(SRCS)

clean:

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re