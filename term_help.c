/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 21:57:33 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 21:57:35 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_hist_save(char **line)
{
	int		fd;
	char	*str;

	write(1, "\n", 1);
	fd = open(g_shell.path_hist, O_RDWR | O_CREAT | O_APPEND, 0600);
	str = ft_strjoin(*line, "\n");
	if (fd != -1 && str && *str != '\n')
		write(fd, str, ft_strlen(str));
	if (**line != '\0')
		ft_doblstadd_front(&g_shell.hist, ft_doblstnew(ft_strdup(*line)));
	close(fd);
	free(str);
	return (0);
}

void	ft_sig_d(struct termios *term)
{
	ft_putendl("exit");
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, term);
	g_shell.sig_fl |= S_D;
	g_shell.err = 0;
	exit(0);
}

int		ft_term_line(char **line, char *str, int l)
{
	int		i;
	int		j;
	int		len;

	if (str == NULL || l == 0)
		return (1);
	len = ft_strlen(*line);
	i = len - 1;
	j = -1;
	write(1, str, l);
	*line = ft_realloc(*line, l + 2);
	while (++i < len + l && str[++j] != '\0')
		if (str[j] > 31 || str[j] < 0)
			(*line)[i] = str[j];
	(*line)[i] = '\0';
	return (0);
}

void	ft_help_term(char **line, char **str, t_doblist **tmp, char **buf)
{
	int		l;
	char	*tmps;

	l = ft_strlen(*str);
	if (!ft_strncmp(*str, "\e[A", 3) && (*tmp) && (*tmp)->prev == NULL &&
!(g_shell.sig_fl & S_NEXT) && !(g_shell.sig_fl & S_PREV))
	{
		tmps = *buf;
		*buf = (!((*tmp)->next) && !((*tmp)->prev)) ?
		ft_strdup("") : ft_strdup(*line);
		free(tmps);
		g_shell.sig_fl |= S_BUF;
	}
	if (!ft_strncmp(*str, "\e[A", 3))
		ft_up(line, tmp);
	else if (!ft_strncmp(*str, "\e[B", 3))
		ft_down(line, tmp, *buf);
	else if (!ft_strncmp(*str, "\e[C", 3) || !ft_strncmp(*str, "\e[D", 3))
		tputs(tigetstr("ed"), 1, ft_putchar_t);
	else if (!ft_strncmp(*str, key_backspace, 3) ||
			!ft_strncmp(*str, "\177", 3))
		ft_backspace(line);
	else
		ft_term_line(line, *str, l);
}

void	ft_read_term(char **line, struct termios *term, t_doblist **tmp)
{
	char			*str;
	char			*buf;
	int				l;

	if (!(str = (char *)malloc(sizeof(char) * 2048)))
		return ;
	str[0] = '\0';
	buf = ft_strdup("");
	g_shell.sig_fl |= S_DOWN;
	while (ft_strncmp(str, "\n", 2))
	{
		if ((l = read(0, str, 100)) == -1)
			break ;
		str[l] = '\0';
		if (g_shell.sig_fl & S_INT && *line)
			sig_help(line);
		if (ft_strchr(str, '\n') != NULL)
			break ;
		if (!ft_strncmp(str, "\4", 2) && (!ft_strlen(*line)))
			ft_sig_d(term);
		else if (ft_strncmp(str, "\4", 2) != 0)
			ft_help_term(line, &str, tmp, &buf);
	}
	free(str);
	free(buf);
}
