/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:49:31 by gsaile            #+#    #+#             */
/*   Updated: 2024/09/26 14:30:24 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "struct.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_line {
	struct s_line	*next;
	char			*line;
}	t_line;

typedef char bool;
#define TRUE 1
#define FALSE 1

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_putnbr_fd(int n, int fd);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putlnbr_base(unsigned long long int nbr, char *base);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_get_len(int n);
int		ft_get_ulen(unsigned int n);
int		ft_lstsize(t_line *lst);
int		ft_printf(const char *format, ...);
int		read_to_list(int fd, t_line **list);
int		has_nl(t_line *list);
int		ft_strlen_and_free(const char *s, t_line **elem, int behavior);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*clear_list(t_line **list, int behavior);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*get_lline(t_line *list);
char	**ft_split(char const *s, char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_front(t_line **lst, t_line *new);
void	ft_lstadd_back(t_line **lst, t_line *new);
void	ft_lstdelone(t_line *lst, void (*del)(void *));
void	ft_lstclear(t_line **lst, void (*del)(void *));
void	ft_lstiter(t_line *lst, void (*f)(void *));
void	parse_arg(const char *format, va_list args, int *counter);
void	clear_list2(t_line **current, t_line **list);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
t_line	*ft_lstnew(void *content);
t_line	*ft_lstlast(t_line *lst);
t_line	*ft_lstmap(t_line *lst, void *(*f)(void *), void (*del)(void *));
t_line	*lst_getlast(t_line *list);

#endif
