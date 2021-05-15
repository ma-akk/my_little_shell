/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntaxerr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:48:35 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/30 21:01:35 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	err_quotes(char *line, int i, int j)
{
	if (line[i] == '\'')
		while (line[j] != 0 && line[j] != '\'')
			j++;
	if (line[i] == '\"')
		while (line[j] != 0 && line[j] != '\"')
		{
			if (line[j] == '\\')
				j++;
			j++;
		}
	return (j);
}

int	err_endoffile(char *line, int *i)
{
	int j;

	j = *i + 1;
	if (line[j] != '\0')
	{
		if (line[*i] == '|')
			j += skip_space(line + j);
		if (line[*i] == '\'' || line[*i] == '\"')
			j = err_quotes(line, *i, j);
		if (j == (int)ft_strlen(line))
			return (1);
	}
	else if (line[*i] == '\'' || line[*i] == '\"' || line[*i] == '|')
		return (1);
	if (line[*i] == '\'' || line[*i] == '\"')
		*i = j;
	return (0);
}

int	err_ut_newline(char *line, int i)
{
	int j;

	j = i + 1;
	if (line[j] != '\0')
	{
		if (line[i] == '>' && line[j] == '>')
		{
			j += skip_space(line + j + 1) + 1;
		}
		if (line[i] == '>' || line[i] == '<')
			while (line[j] == 32)
				j++;
		if (j == (int)ft_strlen(line) && line[i + 1] != '\0')
			return (1);
	}
	else if (line[i] == '>' || line[i] == '<')
		return (1);
	return (0);
}

int	err_ut_before(char *line, int i)
{
	int j;

	j = i - 1;
	if ((line[i] == ';' || line[i] == '|') && i == skip_space(line))
		return (synerror_exit(3, &line[i]));
	if (line[i] == ';' || line[i] == '|')
	{
		while (j > -1 && line[j] == 32)
			j--;
		if (line[j] == ';' || line[j] == '|')
			return (synerror_exit(3, &line[i]));
	}
	return (0);
}

int	err_ut_after(char *line, int i)
{
	int j;

	j = i + 1;
	if (line[i] == '>' && line[j] == '>')
	{
		j += skip_space(line + j + 1) + 1;
		if (line[j] == '>' || line[j] == '<' || line[j] == '|' ||
		line[j] == ';' || line[j] == '\0')
			return (synerror_exit(3, &line[j]));
	}
	else if (line[i] == '>' || line[i] == '<')
	{
		j += skip_space(line + j);
		if (line[j] == '>' || line[j] == '<' || line[j] == '|' ||
		line[j] == ';' || line[j] == '\0')
			return (synerror_exit(3, &line[i]));
	}
	return (0);
}
