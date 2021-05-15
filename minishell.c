/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:43:17 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:43:24 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser_shell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;

	if (ft_init_shell(env, -1) != 0 && argc && argv)
		return (1);
	line = NULL;
	printf("Запуск MiniSHELL ...\n");
	while (1)
	{
		g_shell.sig_fl = S_NONE;
		signal(SIGINT, sig_exit);
		signal(SIGQUIT, sig_quit);
		write(1, "minishell> ", 11);
		if (!(ft_term(&line)) && line != NULL)
		{
			if (!check_syntax(line) && *line != '\0')
				parser_start(line);
			free(line);
			line = NULL;
		}
	}
	exit(1);
}
