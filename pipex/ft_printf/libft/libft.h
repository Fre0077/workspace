/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:57:20 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/27 15:09:56 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int				ft_isalpha(int a);
int				ft_toupper(int a);
int				ft_isdigit(int a);
int				ft_tolower(int a);
int				ft_isalnum(int a);
int				ft_isascii(int a);
int				ft_isprint(int a);
int				ft_atoi(const char *str);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
int				ft_putnbr_un(unsigned int n);

void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putendl_fd(char *s, int fd);
void			*ft_memset(void *buffer, int c, size_t count);
void			*ft_bzero(void *buffer, size_t count);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

size_t			ft_strlen(const char *str);

char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strdup(const char *s1);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			**ft_split(char const *s, char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void	*));
void			ft_lstiter(t_list *lst, void (*f)(void *));

int				ft_lstsize(t_list *lst);

#endif