/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:48:47 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/20 20:48:49 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	parser_shield(char *line, char fl)
{
	int i;

	i = 0;
	if (fl == 'q')
		if (line[1] == '$' || line[1] == '\\' ||
			line[1] == '\"' || line[1] == '`')
			i++;
	if (fl == 'a')
		i++;
	return (i);
}

int	parser_sin_quotes(char *line, t_str *str)
{
	int i;

	i = 0;
	while (line[i] != 0 && line[i] != '\'')
	{
		str->new_arg[str->i_arg] = line[i];
		str->i_arg++;
		i++;
	}
	str->new_arg[str->i_arg] = 0;
	return (i);
}

int	parser_doub_quotes(char *line, t_str *str)
{
	int i;

	i = 0;
	while (line[i] != 0 && line[i] != '\"')
	{
		if (line[i] == '\\')
			i += parser_shield(line + i, 'q');
		else if (line[i] == '$' && (ft_isalnum(line[i + 1]) ||
		line[i + 1] == '?' || line[i + 1] == '_'))
		{
			i += parser_env(line + i + 1, str) + 1;
			add_env_value(str);
			continue ;
		}
		str->new_arg[str->i_arg] = line[i];
		i++;
		str->i_arg++;
		str->new_arg[str->i_arg] = 0;
	}
	str->new_arg[str->i_arg] = 0;
	return (i);
}
