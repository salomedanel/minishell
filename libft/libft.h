/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:25:58 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/13 12:00:27 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//conversions
double				ft_atof(const char *nptr);
int					ft_atoi(const char *nptr);
long long			ft_atoll(const char *nptr);
char				*ft_itoa(int n);
unsigned long long	ft_uatoll(const char *nptr);

//memory functions
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

//ASCII
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspecialchar(int c);

//str
int					ft_countchar(char *str, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *src);
size_t				ft_strlcat(char *dest, char *src, size_t size);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
int					ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_substr(char const *s,
						unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);

//random functions
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_swap(void *a, void *b, int size);
int					ft_tolower(int c);
int					ft_toupper(int c);

//file descriptors
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);

//linked lists
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
//printf
int					ft_printf(const char *s, ...);
int					ft_printchar(int c);
int					ft_printstr(char *s);
int					ft_printnbr(int n);
int					ft_percent(void);
int					ft_printhex(unsigned int hex);
int					ft_printhexmaj(unsigned int hexmaj);
int					ft_printptr(unsigned long long ptr);
int					ft_printuint(unsigned int n);

//GNL
int					ft_strlen_gnl(char *str);
char				*ft_strcpy_gnl(char *s1, char *s2);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_strchr_gnl(char *s, int c);
char				*get_next_line(int fd, int boolean);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#endif
