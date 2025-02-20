# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 13:40:02 by fde-sant          #+#    #+#              #
#    Updated: 2024/11/27 10:59:21 by fde-sant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -g -Wall -Wextra -Werror

FILES =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c\
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
		ft_tolower.c ft_toupper.c ft_putnbr_un.c

BONUS_FILES =	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c\
				ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
					
OBJ = $(FILES:.c=.o)
BONUS_OBJ = $(BONUS_FILES:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean:		clean
	@rm -rf $(NAME)

bonus: 		$(OBJ) $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

re:			fclean all
