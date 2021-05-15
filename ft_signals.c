/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:02:27 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/31 21:35:15 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_exit(int sig)
{
	pid_t pid;

	pid = waitpid(0, 0, WNOHANG);
	g_shell.sig_fl |= S_INT;
	if (!pid)
	{
		kill(pid, sig);
		if (!(g_shell.sig_fl & S_D))
			g_shell.err = 130;
	}
	else if (pid < 0)
	{
		write(1, "\nminishell> ", 12);
		tputs(save_cursor, 0, ft_putchar_t);
		g_shell.err = 1;
	}
	else
		write(1, "\n", 1);
}

void	sig_quit(int sig)
{
	pid_t pid;

	(void)sig;
	g_shell.sig_fl |= S_QUIT;
	pid = waitpid(-1, (int*)&g_shell.err, WNOHANG);
	if (!pid)
	{
		write(1, "Quit: 3\n", 9);
		if (!(g_shell.sig_fl & S_D))
			g_shell.err = 131;
	}
}

void	sig_help(char **line)
{
	free(*line);
	*line = ft_strdup("");
	g_shell.sig_fl &= ~(S_INT);
}
