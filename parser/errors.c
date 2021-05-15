/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:49:53 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:13:37 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	synerror_exit(int code, char *err)
{
	if (code == 1)
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
	if (code == 2)
		write(2, "minishell: syntax error near unexpected token `newline'\n",
		57);
	if (code == 3)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, err, 1);
		ft_putendl_fd("'", 2);
	}
	g_shell.err = 258;
	return (1);
}

int	curerror_exit(int code, char *err, char *filename)
{
	if (code == 5)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		ft_putendl_fd(err, 2);
		g_shell.err = 1;
	}
	return (1);
}

int	memerror_exit(int code, char *err)
{
	if (code == 6)
	{
		write(2, "minishell: ", 11);
		ft_putendl_fd(err, 2);
		g_shell.err = 1;
	}
	return (-1);
}
