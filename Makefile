NAME=webserv

HEADERS = \
headers/colours.hpp \
headers/Config.hpp \
headers/Extern.hpp \
headers/Request.hpp \
headers/webserv.hpp

SRCS = \
srcs/CGI.cpp \
srcs/Config.cpp \
srcs/Extern.cpp \
srcs/init.cpp \
srcs/main.cpp \
srcs/Request.cpp \
srcs/response.cpp

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME)

$(NAME): $(SRCS)
	c++ $(CPPFLAGS) -o $(NAME) $(SRCS) -Iheaders/

clean:

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

VAL_FLAGS = \
--leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--log-file=val.log


val: $(NAME) $(HEADERS)
	clear
	@echo "Recompiling webserv..."
	make re
	@echo "Running webserv with valgrind..."
	valgrind $(VAL_FLAGS) ./webserv 1.config