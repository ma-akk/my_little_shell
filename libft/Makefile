SRCS		=   ft_memset.c ft_bzero.c \
                ft_memcpy.c ft_memccpy.c \
                ft_memmove.c ft_memchr.c \
                ft_memcmp.c ft_strlen.c \
                ft_strlcpy.c ft_strlcat.c \
                ft_strchr.c ft_strrchr.c \
                ft_strnstr.c ft_strncmp.c \
                ft_atoi.c ft_isalnum.c \
                ft_isalpha.c ft_isascii.c \
                ft_isdigit.c ft_isprint.c \
                ft_toupper.c ft_tolower.c \
                ft_strdup.c ft_calloc.c \
                ft_substr.c ft_strjoin.c \
                ft_strtrim.c ft_split.c \
                ft_itoa.c ft_strmapi.c \
                ft_putchar_fd.c	ft_putstr_fd.c \
                ft_putendl_fd.c ft_putnbr_fd.c \
                ft_lstnew.c ft_lstadd_front.c \
                ft_lstsize.c ft_lstlast.c \
                ft_lstadd_back.c ft_lstdelone.c \
                ft_lstclear.c ft_lstiter.c \
                ft_lstmap.c ft_realloc.c \
                ft_putchar.c ft_putstr.c \
                ft_putnbr.c ft_itoa_base.c \
                get_next_line.c btree_sort.c \
                ft_tree.c ft_doblist.c

OBJC		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME):	${OBJC}
			ar rc libft.a ${OBJC}

all:		${NAME}

bonus:		all

clean:		
			${RM} ${OBJC}

fclean:		clean
			${RM} ${NAME}

re:			fclean	all

.PHONY:		all clean fclean re
