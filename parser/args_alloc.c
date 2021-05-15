/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:56:14 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:35:35 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

t_arg	**args_alloc(t_pars *pars)
{
	t_arg	**args;
	t_arg	*start;
	int		i;
	int		n;

	i = 0;
	n = pars->count_struct + 1;
	args = (t_arg **)malloc(n * sizeof(t_arg *) + n * sizeof(t_arg));
	if (args)
	{
		start = (t_arg *)((char *)args + n * sizeof(t_arg *));
		while (i < n)
		{
			args[i] = start + i;
			args[i]->fl = F_NONE;
			i++;
		}
	}
	return (args);
}

void	pars_free(t_pars *pars)
{
	pars->str = (t_str *)simple_free(pars->str);
	pars->file_in = (char *)simple_free(pars->file_in);
	pars->file_out = (char *)simple_free(pars->file_out);
}

void	struct_free(t_arg *args)
{
	int j;

	j = 0;
	while (args->arg[j] != NULL)
	{
		args->arg[j] = (char *)simple_free(args->arg[j]);
		j++;
	}
	if ((args->fl & F_REDA) || (args->fl & F_REDT))
		close(args->red_fd[1]);
	if (args->fl & F_REDI)
		close(args->red_fd[0]);
	free(args->arg[j]);
	args->arg[j] = NULL;
	free(args->arg);
}

void	args_free(t_pars *pars)
{
	int		i;

	i = 0;
	pars_free(pars);
	while (g_shell.args[i] != NULL)
	{
		struct_free(g_shell.args[i]);
		i++;
	}
	free(g_shell.args[i]);
	g_shell.args[i] = NULL;
	if (g_shell.args)
	{
		free(g_shell.args);
		g_shell.args = NULL;
	}
}

void	*simple_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}
