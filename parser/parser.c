/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:50:40 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:20:16 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	check_syntax(char *line)
{
	int	i;

	if (line == NULL)
		return (1);
	i = skip_space(line);
	while (line[i] != '\0')
	{
		if (err_ut_newline(line, i))
			return (synerror_exit(2, NULL));
		if (err_ut_before(line, i) || err_ut_after(line, i))
			return (1);
		if (err_endoffile(line, &i))
			return (synerror_exit(1, NULL));
		if (line[i] == '\\')
			i++;
		i++;
	}
	return (0);
}

int	parser_sim(char *line, t_str *str)
{
	int i;

	i = 0;
	if (line[i] == '\\')
		i += parser_shield(line + i, 'a');
	str->new_arg[str->i_arg] = line[i];
	i++;
	str->i_arg++;
	str->new_arg[str->i_arg] = 0;
	return (i);
}

int	parser_new_arg(char *line, t_str *str, int i)
{
	if (line[i] == '\'')
		i += parser_sin_quotes(line + i + 1, str) + 2;
	else if (line[i] == '\"')
		i += parser_doub_quotes(line + i + 1, str) + 2;
	else if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		i++;
	else if (line[i] == '$' && (ft_isalnum(line[i + 1])
	|| line[i + 1] == '?' || line[i + 1] == '_'))
	{
		i += parser_env(line + i + 1, str) + 1;
		add_env_value(str);
	}
	else
		i += parser_sim(line + i, str);
	return (i);
}

int	parser_arg(char *line, t_pars *pars, t_arg *args)
{
	int i;
	int red;

	i = skip_space(line);
	while (line[i] != 32 && line[i] != ';' && line[i] != '\0' && line[i] != '|')
	{
		if (line[i] != '>' && line[i] != '<')
			i = parser_new_arg(line, pars->str, i);
		else
		{
			while (line[i] == '>' || line[i] == '<')
			{
				if ((red = parser_red(line + i, pars, args)) < 0)
					return (-1);
				i += red + skip_space(line + i + red);
			}
		}
	}
	return (i);
}

int	parser_start(char *line)
{
	int		i;
	char	*new_line;
	t_pars	pars;

	i = skip_space(line);
	while (line[i] != '\0')
	{
		if (!(new_line = pre_parser_env(line + i)))
			return (memerror_exit(6, strerror(errno)));
		init_pars(&pars);
		i += skip_cur_struct(line + i);
		check_count_struct(new_line, &pars);
		if (pars.str == NULL || g_shell.args == NULL)
			return (memerror_exit(6, strerror(errno)));
		if (add_arg(new_line, &pars) < 0)
			return (-1);
		pars.str->size_arg = 0;
		ft_processor();
		i += skip_space(line + i);
		if (line[i] == ';' || (line[i] != 0 && line[i + 1] == '\0'))
			i++;
		args_free(&pars);
		new_line = (char *)simple_free(new_line);
	}
	return (0);
}
