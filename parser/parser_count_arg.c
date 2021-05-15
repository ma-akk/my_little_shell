/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:31:13 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:17:25 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	check_count_arg(char *line, t_pars *pars)
{
	int		i;

	i = skip_space(line);
	while (line[i] != ';' && line[i] != '|' && line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
			i += skip_red(line + i);
		else
		{
			while (line[i] != 0 && !ft_strchr(SEPARAT, line[i]))
			{
				if (line[i] == '\\')
					i += skip_shield(line + i);
				else if (line[i] == '\'' || line[i] == '\"')
					i += skip_quotes(line + i);
				else
					i++;
			}
			pars->count_arg++;
		}
		i += skip_space(line + i);
	}
	return (i);
}

int	check_count_struct(char *line, t_pars *pars)
{
	int i;

	i = skip_space(line);
	while (line[i] != ';' && line[i] != '\0')
	{
		if (line[i] == '\\')
			i += skip_shield(line + i);
		else if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(line + i);
		else if (line[i] == '|')
		{
			pars->count_struct++;
			i++;
		}
		else
			i++;
	}
	g_shell.args = args_alloc(pars);
	return (i);
}

int	skip_cur_struct(char *line)
{
	int i;

	i = skip_space(line);
	while (line[i] != ';' && line[i] != '\0')
	{
		if (line[i] == '\\')
			i += skip_shield(line + i);
		else if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(line + i);
		else
			i++;
	}
	return (i);
}
