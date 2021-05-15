/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:43:37 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:43:41 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include "libft/libft.h"
# define F_NONE		0b00000000
# define F_PIPE		0b00000001
# define F_SEM		0b00000010
# define F_REDA		0b00000100
# define F_REDT		0b00001000
# define F_REDI		0b00010000
# define F_RED		0b00011100
# define S_NONE		0b00000000
# define S_INT		0b00000001
# define S_QUIT		0b00000010
# define S_D		0b00000100
# define S_SIG		0b00000111
# define S_NEXT		0b00001000
# define S_PREV		0b00010000
# define S_BUF		0b00100000
# define S_DOWN		0b01000000
# define S_ONE		0b10000000

typedef struct		s_arg
{
	char			**arg;
	unsigned char	fl;
	int				pip_fd[2];
	unsigned int	red_fd[2];
}					t_arg;

typedef struct		s_shell
{
	t_arg			**args;
	t_list			*env;
	t_doblist		*hist;
	char			*path_hist;
	unsigned int	err;
	unsigned char	sig_fl;
	unsigned int	true_fd[2];
}					t_shell;

t_shell				g_shell;

int					ft_pwd(void);
int					ft_cd(char **arg);
int					ft_echo(char **arg);
int					ft_init_shell(char **env, int i);
int					ft_env(char **arg, int i);
int					ft_export(char **arg);
int					ft_execve(char **arg);
int					ft_unset(char **arg, int i, int ret);
int					ft_exit(char **arg);
int					ft_processor(void);
int					ft_pult(char **arg, int i, int err);
int					ft_insert_arg(char *arg);
int					ft_pipe(t_arg **args);
int					ft_term(char **line);
void				sig_exit(int sig);
void				sig_quit(int sig);
int					ft_hist_save(char **line);
void				ft_sig_d(struct termios *term);
int					ft_putchar_t(int c);
int					ft_backspace(char **line);
void				ft_up(char **line, t_doblist **tmp);
void				ft_down(char **line, t_doblist **tmp, char *buf);
void				ft_read_term(char **line, struct termios *term,
					t_doblist **tmp);
int					ft_execve_pipe(char **arg);
int					ft_redirect(int flag, int i);
int					ft_pult_pipe(char **arg, int i, int err);
void				sig_help(char **line);

#endif
