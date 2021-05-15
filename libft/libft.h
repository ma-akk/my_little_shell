/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:04:43 by dcordeli          #+#    #+#             */
/*   Updated: 2020/11/08 20:58:47 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <ctype.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_doblist
{
	void				*content;
	struct s_doblist	*next;
	struct s_doblist	*prev;
}				t_doblist;

typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
	void			*key;
}				t_btree;

typedef struct	s_gnl
{
	int				fd;
	char			*buf;
	struct s_gnl	*next;
}				t_gnl;

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlen_c(const char *s, char c);
size_t			ft_strlen_l(const wchar_t *s);
size_t			ft_strlcpy (char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *h, const char *n, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strdup(const char *s);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(long long int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putendl(char *s);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
t_list			*ft_lstdelnote(t_list *begin, t_list *tmp, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
char			*ft_realloc(char *ptr, size_t size);
void			ft_putchar(char c);
void			ft_putstr(char *s, int len);
void			ft_putstr_l(wchar_t *s, int len);
void			ft_putnbr(int n);
char			*ft_itoa_base(unsigned long long int n, char c);
int				get_next_line(int fd, char **line);
t_btree			**ft_balance(t_btree **node, int len);
t_btree			*btree_create_node(void *key, void *item);
void			btree_apply_prefix(t_btree *root, void (*applyf)(t_btree *));
void			btree_apply_infix(t_btree *root, void (*applyf)(t_btree *));
void			btree_apply_suffix(t_btree *root, void (*applyf)(t_btree *));
t_doblist		*ft_doblstnew(void *content);
void			ft_doblstadd_front(t_doblist **lst, t_doblist *new);
int				ft_strchr_i(const char *s, int c);
long long int	ft_atoill(const char *nptr);
int				ft_allisdigit(char *s);
int				ft_alltolower(char *s);
int				ft_allisprint(char *s);
int				ft_strlen_m(const char *s, char c);

#endif
