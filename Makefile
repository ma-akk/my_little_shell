SRCS    	=       minishell.c processor.c \
					init.c parser/args_alloc.c \
					parser/errors.c parser/parser.c \
					parser/parser_count_arg.c \
					parser/parser_count_arg_utils.c \
					parser/preparser_env.c \
					parser/parser_env.c \
					parser/parser_quotes.c \
					parser/parser_redirect.c \
					parser/parser_syntaxerr.c \
					built_in/cd.c built_in/echo.c \
					built_in/env.c built_in/execve.c \
					built_in/exit.c built_in/export.c \
					built_in/pwd.c built_in/unset.c \
					pipe.c parser/parser_add_arg.c \
					parser/parser_init.c term.c ft_signals.c \
					term_help.c built_in/execve_pipe.c

#SRCSB		=		main_bonus.c

INCLUDE		=		minishell.h parser/parser_shell.h

#INCBONUS	=		minishell_bonus.h

OBJC    	=       ${SRCS:.c=.o}

#OBJCB    	=		${SRCSB:.c=.o}

LIBS		=		libft.a

NAME		=       minishell

CC      	=       gcc

FLAGS		=		-Wall -Wextra -Werror

RM			=       rm -rf

%.o:			%.c $(INCLUDE)
				$(CC) $(FLAGS) -g -I. -c $< -o ${<:.c=.o}

all:            $(NAME)

$(NAME):        $(OBJC)
				make -C libft/
				$(CC) $(OBJC) -g -Llibft -lft -ltermcap -o $(NAME)

#bonus:			$(OBJCB)
#				make -C libft/
#				$(CC) $(OBJCB) -Llibft -lft -I.$(INCBONUS) -o $(NAME)

clean:
				${RM} ${OBJC}
				make clean -C libft/

fclean:			clean
				${RM} ${NAME}
				make fclean -C libft/

re:				fclean	all

.PHONY:			all clean fclean re