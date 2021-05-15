/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:44:51 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:44:54 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_check_n(char *str)
{
	int i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int				ft_echo(char **arg)
{
	char	f;
	int		i;

	f = 0;
	i = 0;
	while (arg[++i] != NULL && ft_check_n(arg[i]) == 1)
		f = 1;
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[++i] != NULL)
			ft_putchar(' ');
	}
	if (f == 0)
		ft_putchar('\n');
	return (0);
}
