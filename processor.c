/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:44:02 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:44:04 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_redirect(int flag, int i)
{
	if ((g_shell.args[i]->fl & F_RED) && flag == 0)
	{
		if (g_shell.args[i]->fl & F_REDA || g_shell.args[i]->fl & F_REDT)
			dup2(g_shell.args[i]->red_fd[1], 1);
		if (g_shell.args[i]->fl & F_REDI)
			dup2(g_shell.args[i]->red_fd[0], 0);
	}
	if (g_shell.args[i]->fl & F_RED && flag == 1 &&
		!(g_shell.args[i]->fl & F_PIPE))
	{
		if (g_shell.args[i]->fl & F_REDA || g_shell.args[i]->fl & F_REDT)
			dup2(g_shell.true_fd[1], 1);
		if (g_shell.args[i]->fl & F_REDI)
			dup2(g_shell.true_fd[0], 0);
	}
	if (g_shell.args[i]->fl & F_RED && flag == 1 &&
		(g_shell.args[i]->fl & F_PIPE))
	{
		if (g_shell.args[i]->fl & F_REDA || g_shell.args[i]->fl & F_REDT)
			dup2(g_shell.args[i]->pip_fd[1], 1);
		if (g_shell.args[i]->fl & F_REDI)
			dup2(g_shell.args[i]->pip_fd[0], 0);
	}
	return (0);
}

int				ft_pult(char **arg, int i, int err)
{
	if (arg == NULL || arg[0] == NULL)
		return (0);
	ft_redirect(0, i);
	if (!ft_strncmp("pwd", arg[0], 10) && ft_strlen(arg[0]) == 3)
		err = ft_pwd();
	else if (!ft_strncmp("cd", arg[0], 10) && ft_strlen(arg[0]) == 2)
		err = ft_cd(arg);
	else if (!ft_strncmp("echo", arg[0], 10) && ft_strlen(arg[0]) == 4)
		err = ft_echo(arg);
	else if (!ft_strncmp("env", arg[0], 10) && ft_strlen(arg[0]) == 3)
		err = ft_env(arg, i);
	else if (!ft_strncmp("export", arg[0], 10) && ft_strlen(arg[0]) == 6)
		err = ft_export(arg);
	else if (!ft_strncmp("unset", arg[0], 10) && ft_strlen(arg[0]) == 5)
		err = ft_unset(arg, 0, 0);
	else if (!ft_strncmp("exit", arg[0], 10) && ft_strlen(arg[0]) == 4)
		err = ft_exit(arg);
	else
		err = ft_execve(arg);
	if (!(g_shell.sig_fl & S_INT) && !(g_shell.sig_fl & S_QUIT))
		g_shell.err = err;
	ft_redirect(1, i);
	return (err);
}

int				ft_processor(void)
{
	if (!g_shell.args || !g_shell.args[0] ||
		!g_shell.args[0]->arg || !g_shell.args[0]->arg[0])
		return (0);
	if ((g_shell.args[0]->fl & F_PIPE) == 0)
		ft_pult(g_shell.args[0]->arg, 0, 0);
	else
		ft_pipe(g_shell.args);
	return (0);
}
