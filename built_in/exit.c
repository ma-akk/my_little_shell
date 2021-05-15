/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:45:39 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:45:41 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_exit_error(char *str)
{
	if (str == NULL)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (255);
	}
	g_shell.err = 1;
	return (1);
}

int				ft_exit(char **arg)
{
	int			len;
	int			l;
	long long	n;

	l = 0;
	if ((g_shell.args[0]->fl & F_PIPE) == 0)
		ft_putendl("exit");
	while (arg[l] != NULL)
		l++;
	if (l == 1)
		exit(g_shell.err);
	len = ft_strlen_c(arg[1], '0');
	n = ft_atoill(arg[1]);
	if (len > 20 || (len == 20 && (ft_isdigit(arg[1][0]) || n > 0)) ||
		(len == 19 && ft_isdigit(arg[1][0]) && n < 0) ||
		ft_allisdigit(arg[1] + 1) == 0 ||
		(ft_isdigit(arg[1][0]) == 0 && arg[1][0] != '-'))
		exit(ft_exit_error(arg[1]));
	else if (l > 2)
		return (ft_exit_error(NULL));
	exit((unsigned char)n);
	return (0);
}
