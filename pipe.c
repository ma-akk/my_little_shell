/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:43:52 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:43:54 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipe_close(t_arg **args)
{
	int i;

	i = -1;
	while (args[++i] != NULL)
	{
		close(args[i]->pip_fd[0]);
		close(args[i]->pip_fd[1]);
	}
	dup2(g_shell.true_fd[0], 0);
	dup2(g_shell.true_fd[1], 1);
	return (0);
}

static int	ft_pipe_help(t_arg **args, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		close(args[i]->pip_fd[1]);
	if (pid == 0)
	{
		if (i > 0)
		{
			close(args[i - 1]->pip_fd[1]);
			dup2(args[i - 1]->pip_fd[0], 0);
			close(args[i - 1]->pip_fd[0]);
		}
		if (args[i + 1] != NULL)
		{
			close(args[i]->pip_fd[0]);
			dup2(args[i]->pip_fd[1], 1);
			close(args[i]->pip_fd[1]);
		}
		else
			dup2(g_shell.true_fd[1], 1);
		exit(ft_pult_pipe(args[i]->arg, i, 0));
	}
	return ((int)pid);
}

int			ft_pipe(t_arg **args)
{
	int		i;

	i = -1;
	while (args[++i] != NULL)
		pipe(args[i]->pip_fd);
	i = -1;
	while (args[++i] != NULL)
		ft_pipe_help(args, i);
	ft_pipe_close(args);
	i = -1;
	while (args[++i] != NULL)
		wait(0);
	return (ft_pipe_close(args));
}
