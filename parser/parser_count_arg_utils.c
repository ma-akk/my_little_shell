/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_arg_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:18:26 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:19:07 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	skip_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

int	skip_shield(char *line)
{
	int i;

	i = 0;
	while (line[i] == '\\')
		i += 2;
	return (i);
}

int	skip_quotes(char *line)
{
	int i;

	i = 1;
	if (line[0] == '\'')
		while (line[i] != '\'')
			i++;
	else if (line[0] == '\"')
		while (line[i] != '\"')
		{
			if (line[i] == '\\')
				i++;
			i++;
		}
	return (i + 1);
}

int	skip_red(char *line)
{
	int i;

	i = 0;
	while (line[i] == '>' || line[i] == '<')
	{
		if (line[i] == '>' && line[i + 1] == '>')
			i++;
		i++;
		i += skip_space(line + i);
		while (line[i] != 32 && line[i] != '>' && line[i] != '<' &&
				line[i] != ';' && line[i] != '|' && line[i] != '\0')
		{
			if (line[i] == '\\')
				i += skip_shield(line + i);
			else if (line[i] == '\'' || line[i] == '\"')
				i += skip_quotes(line + i);
			else
				i++;
		}
		i += skip_space(line + i);
	}
	return (i);
}
