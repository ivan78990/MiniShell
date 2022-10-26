/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:45:26 by warchang          #+#    #+#             */
/*   Updated: 2020/11/20 17:36:41 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 32
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int					ft_countwords(char const *str, char c);
int					ft_strequ(char const *s1, char const *s2);
long				ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(char c);
char				*ft_itoa(int nb);
void				ft_freestrarr(char **arr);
char				*ft_pathjoin(char *p1, char *p2);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *arr, int c, size_t n);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char *s);
void				ft_putnstr(char *str, int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstr(char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *str, int ch);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *str);
int					ft_strendswith(char *s1, char *s2);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strjoinch(char const *s1, char c);
char				*ft_strjoinchcl(char *s1, char c);
char				*ft_strjoincl(char *s1, char *s2, int free_both);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strrchr(char *str, int ch);
char				**ft_split(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strreplace(char *str, char *term, char *replace_by);
char				**ft_strsplit(char const *s, char c);
int					ft_strstartswith(char *s1, char *s2);
int					ft_tolower(int c);
int					ft_toupper(int c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void*));

int					mycheck_int(int fd, char **line);
int					get_next_line(int fd, char **line);
//void				my_putstr(char *str);
size_t				gnl_strlen(const char *str);
char				*my_strjoin(char *s1, char *s2);
int					nlbuff(char *buff);
char				*linefrom_buff(char *buff);
int					stdin_read(char **line);
char				*buff_trim(char *buff, size_t len);
void				gnl_strlcpy(char *dest, const char *src, size_t size);
char				*start_buff_init(char *buff, int fd);
#endif
