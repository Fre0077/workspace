/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:36:46 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/19 11:04:12 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "external.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// my_lst
/**
 * @brief Adds the element ’new’ at the end of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the element to be added to the list.
 * @return void
 * 
 * @note The function is located in the file `ft_lstadd_back.c`
 * 
 * @see ft_lstadd_front
 */
void			ft_lstadd_back(t_list **lst, t_list *new);
/**
 * @brief Adds the element ’new’ at the beginning of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the element to be added to the list.
 * @return void
 * 
 * @note The function is located in the file `ft_lstadd_front.c`
 */
void			ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Clear the list and free the memory of the elements using the 
 * 			function ’del’ and free the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param del The address of the function used to delete the content of 
 * 			the element.
 * @return void
 * 
 * @note The function is located in the file `ft_lstclear.c`
 * 
 * @see ft_lstdelone
 */
void			ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief Delete and free the memory of the element ’lst’ using the 
 * 			function ’del’.
 * @param lst The element to be deleted.
 * @param del The address of the function used to delete the content of 
 * 			the element.
 * @return void
 * 
 * @note The function is located in the file `ft_lstdelone.c`
 * 
 * @pre The free function from the library <stdlib.h> is included.
*/
void			ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ to the 
 * 			content of each element.
 * @param lst The address of a pointer to the first link of a list.
 * @param f The address of the function used to iterate on the list.
 * @return void
 * 
 * @note The function is located in the file `ft_lstiter.c`
 */
void			ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * @brief Returns the last element of the list.
 * @param lst The first element of the list.
 * @return The last element of the list.
 * 
 * @note The function is located in the file `ft_lstlast.c`
 */
t_list			*ft_lstlast(t_list *lst);
/**
 * @brief Creates a new list with the result of the function ’f’ applied to 
 * 			the content of each element of the list.
 * @param lst The first element of the list.
 * @param f The address of the function used to create the new list.
 * @param del The address of the function used to delete the content of 
 * 			the element.
 * @return The new list.
 * 
 * @note The function is located in the file `ft_lstmap.c`
 */
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
/**
 * @brief Creates a new element of the list.
 * @param content The content of the new element.
 * @return The new element.
 * 
 * @note The function is located in the file `ft_lstnew.c`
 */
t_list			*ft_lstnew(void *content);
/**
 * @brief Returns the number of elements in a list.
 * @param lst The first element of the list.
 * @return The number of elements in the list.
 * 
 * @note The function is located in the file `ft_lstsize.c`
 */
int				ft_lstsize(t_list *lst);

// my_mem
/**
 * @brief Allocates memory for an array of ’count’ elements of ’size’ bytes
 * 			each and returns a pointer to the allocated memory.
 * @param count The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory.
 */
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_free_mat(void **mat);
void			*ft_free_mat_char(char **mat);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);

// my_nbr
int				ft_abs(int nb);
long			ft_labs(long nb);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_no_sign(int n);
int				ft_log(int nb, int base);
unsigned int	ft_ulog(unsigned int nb, unsigned int base);
size_t			ft_stlog(size_t nb, size_t base);
long			ft_llog(long nb, long base);
//int				ft_ullog(unsigned long nb, int base);
int				ft_pow(int nb, int power);
unsigned int	ft_upow(unsigned int nb, unsigned int power);
size_t			ft_stpow(size_t nb, size_t power);
long			ft_lpow(long nb, long power);
int				ft_sqrt(int nb);
unsigned int	ft_usqrt(unsigned int nb);
size_t			ft_stsqrt(size_t nb);
long			ft_lsqrt(long nb);

// my_put
int				ft_putchar(char c);
int				ft_putchar_fd(char c, int fd);
int				ft_putendl(char *s);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr(int n);
int				ft_putnbr_fd(int n, int fd);
int				ft_putstr(char *s);
int				ft_putstr_fd(char *s, int fd);

// my_str
char			**ft_append_line(char **map, char *line);
int				ft_char_count(char *str, char c);
int				ft_matchr_count(char **mat, char c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
char			*ft_pend_char(char *str, int n, char c, int append);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strnchr(const char *s, int c, size_t len);
int				ft_matchr(char **mat, char c);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s, size_t len);
char			*str_dup_till_charset(const char *str, const char *charset);
char			**ft_char_mat_dup(char **mat);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin_free_1(char *s1, char *s2);
char			*ft_strjoin_mat(char **mat, char *sep);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free_1_2(char const *s1, char const *s2);
char			*ft_strjoin_free_2(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
int				ft_strlen_int(const char *str);
int				ft_char_mat_len(char **mat);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strtrim_free(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

#endif