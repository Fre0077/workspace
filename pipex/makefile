# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 09:01:52 by fde-sant          #+#    #+#              #
#    Updated: 2025/03/11 15:41:39 by alborghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
printf = printf/printf.a
DIR_printf = printf/
GET_NEXT_LINE = get_next_line/get_next_line.a
DIR_GET_NEXT_LINE = get_next_line/
FLAGS = -Wall -Wextra -Werror -g

FILE = pipex.c ft_split_add.c utils.c get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c

OBJ = $(FILE:.c=.o)

all:		$(NAME) $(printf)
	@cc pipex.c $(NAME) $(printf) $(FLAGS) -o "pipex"
	@$(MAKE) fclean -C $(DIR_printf)
	@make fclean

$(printf):	
	@$(MAKE) -C $(DIR_printf)

$(NAME):	$(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "created pipex"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "removed .o"

fclean:		clean
	@rm -rf $(NAME)
	@echo "removed .a"

re:			fclean all

.SILENT:

# run: re clean
# 	@cc pipex.c pipex.a $(FLAGS) -o "pipex"