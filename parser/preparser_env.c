/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:22:35 by dcordeli          #+#    #+#             */
/*   Updated: 2021/04/26 10:22:37 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

static int	argcpy(char *line, t_str *arg_env, int i)
{
	arg_env->new_arg[arg_env->i_arg] = line[i];
	arg_env->i_arg++;
	i++;
	arg_env->new_arg[arg_env->i_arg] = 0;
	return (i);
}

int			input_new_line(char *line, t_str *arg_env, int i)
{
	if (line[i] == '\\')
		i = argcpy(line, arg_env, i);
	else if (line[i] == '\"')
	{
		i = argcpy(line, arg_env, i);
		while (line[i] != 0 && line[i] != '\"')
			i = argcpy(line, arg_env, i);
	}
	else if (line[i] == '\'')
	{
		i = argcpy(line, arg_env, i);
		while (line[i + 1] != 0 && line[i + 1] != '\"')
			i = argcpy(line, arg_env, i);
	}
	i = argcpy(line, arg_env, i);
	return (i);
}

char		*pre_parser_env(char *line)
{
	int		i;
	t_str	arg_env;

	i = 0;
	i += skip_space(line);
	init_str(&arg_env, ft_strlen(line + i));
	arg_env.size_arg = ft_strlen(line + i);
	if (arg_env.new_arg == NULL)
		return (NULL);
	while (line[i] != 0 && line[i] != ';')
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			i += parser_env(line + i + 1, &arg_env) + 1;
			add_env_value(&arg_env);
			continue;
		}
		else
			i = input_new_line(line, &arg_env, i);
	arg_env.new_arg[arg_env.i_arg] = '\0';
	arg_env.new_env = (char *)simple_free(arg_env.new_env);
	arg_env.size_arg = 0;
	return (arg_env.new_arg);
}
