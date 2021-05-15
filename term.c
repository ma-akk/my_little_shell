/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:44:20 by dcordeli          #+#    #+#             */
/*   Updated: 2021/04/07 12:19:17 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putchar_t(int c)
{
	return (write(1, &c, 1));
}

int		ft_backspace(char **line)
{
	int l;

	l = ft_strlen(*line);
	if (l > 0)
	{
		tputs(cursor_left, 1, ft_putchar_t);
		tputs(tgetstr("dc", 0), 1, ft_putchar_t);
		(*line)[l - 1] = '\0';
	}
	return (0);
}

void	ft_up(char **line, t_doblist **tmp)
{
	char *tmpc;

	if (!(*tmp))
		return ;
	tmpc = *line;
	tputs(restore_cursor, 1, ft_putchar_t);
	tputs(tigetstr("ed"), 1, ft_putchar_t);
	if ((*tmp)->next != NULL)
	{
		if (!(g_shell.sig_fl & S_BUF))
			*tmp = (*tmp)->next;
		g_shell.sig_fl |= S_NEXT;
		g_shell.sig_fl &= ~(S_PREV);
	}
	else
		g_shell.sig_fl &= ~(S_NEXT);
	if (!((*tmp)->next) && !((*tmp)->prev) && (g_shell.sig_fl & S_DOWN))
		g_shell.sig_fl |= S_ONE;
	if (!((*tmp)->next) && !((*tmp)->prev) && !(g_shell.sig_fl & S_DOWN))
		g_shell.sig_fl &= S_ONE;
	*line = (!(g_shell.sig_fl & S_NEXT) && !(g_shell.sig_fl & S_ONE))
			? ft_strdup("") : ft_strdup((*tmp)->content);
	ft_putstr_fd(*line, 1);
	free(tmpc);
	g_shell.sig_fl &= ~(S_DOWN | S_BUF);
}

void	ft_down(char **line, t_doblist **tmp, char *buf)
{
	char	*tmpc;

	if (!(*tmp))
		return ;
	tmpc = *line;
	tputs(restore_cursor, 1, ft_putchar_t);
	tputs(tigetstr("ed"), 1, ft_putchar_t);
	if ((*tmp)->prev != NULL)
	{
		if ((*tmp)->next != NULL || (g_shell.sig_fl & S_PREV))
			*tmp = (*tmp)->prev;
		g_shell.sig_fl |= S_PREV;
		g_shell.sig_fl &= ~(S_NEXT);
	}
	else
		g_shell.sig_fl &= ~(S_PREV);
	*line = (!(g_shell.sig_fl & S_PREV))
			? ft_strdup(buf) : ft_strdup((*tmp)->content);
	if (!(g_shell.sig_fl & S_PREV))
		g_shell.sig_fl |= S_BUF;
	ft_putstr_fd(*line, 1);
	free(tmpc);
	g_shell.sig_fl |= S_DOWN;
}

int		ft_term(char **line)
{
	struct termios		term;
	t_doblist			*tmp;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	if (tgetent(NULL, "xterm-256color") == -1)
		return (1);
	*line = NULL;
	tputs(save_cursor, 0, ft_putchar_t);
	if (!(*line = ft_realloc(*line, 2)))
		return (1);
	tmp = g_shell.hist;
	ft_read_term(line, &term, &tmp);
	ft_hist_save(line);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, &term);
	return (0);
}
