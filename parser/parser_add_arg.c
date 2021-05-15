/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:56:54 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:35:31 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	check_empty_env(t_pars *pars, t_arg *args, int iarg)
{
	if (!(pars->str->new_arg[0] == '\0' && (args->fl & F_RED)))
	{
		args->arg[iarg] = pars->str->new_arg;
		pars->str->new_arg = NULL;
		iarg++;
	}
	else if (pars->str->new_arg)
	{
		pars->str->new_arg = (char *)simple_free(pars->str->new_arg);
		pars->count_arg--;
	}
	return (iarg);
}

int	check_size_arg(char *line, t_pars *pars)
{
	int i;

	i = 0;
	while (line[i] != 0 && line[i] != ';' && line[i] != '|'
	&& line[i] != '>' && line[i] != '<')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(line + i);
		else
			i++;
	}
	pars->str->size_arg = i;
	return (i);
}

int	input_arg(char *line, t_pars *pars, t_arg *args)
{
	int i;
	int iarg;
	int check_err;

	i = skip_space(line);
	iarg = 0;
	while (iarg < pars->count_arg)
	{
		init_str(pars->str, ft_strlen(line + i));
		if (pars->str->new_arg == NULL)
			return (memerror_exit(6, strerror(errno)));
		if ((check_err = parser_arg(line + i, pars, args)) < 0)
			return (-1);
		i += check_err;
		pars->str->new_arg[pars->str->i_arg] = '\0';
		iarg = check_empty_env(pars, args, iarg);
	}
	args->arg[iarg] = NULL;
	if ((check_err = parser_arg(line + i, pars, args)) < 0)
		return (-1);
	i += check_err;
	return (i);
}

int	input_fl(t_arg *cur_args, t_pars *pars)
{
	if (pars->count_struct > 1)
		cur_args->fl |= F_PIPE;
	if (pars->file_in)
		cur_args->red_fd[0] = open(pars->file_in, O_RDONLY, 0444);
	if (pars->file_out && (cur_args->fl & F_REDT))
		cur_args->red_fd[1] = open(pars->file_out,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pars->file_out && (cur_args->fl & F_REDA))
		cur_args->red_fd[1] = open(pars->file_out,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	return (0);
}

int	add_arg(char *line, t_pars *pars)
{
	int	j;
	int i;
	int start;

	j = 0;
	i = 0;
	while (j < pars->count_struct)
	{
		start = i;
		pars->count_arg = 0;
		i += check_count_arg(line + start, pars);
		if (!(g_shell.args[j]->arg = (char **)ft_calloc((pars->count_arg + 1),
			sizeof(char *))))
			return (memerror_exit(6, strerror(errno)));
		if (input_arg(line + start, pars, g_shell.args[j]) < 0)
			return (-1);
		input_fl(g_shell.args[j], pars);
		if (line[i] != '\0')
			i++;
		j++;
	}
	g_shell.args[j] = NULL;
	return (0);
}
