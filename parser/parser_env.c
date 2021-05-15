/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:49:45 by gtresa            #+#    #+#             */
/*   Updated: 2021/04/07 12:14:44 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

char	*get_env_name(char *line)
{
	int		i;
	char	*val_env;
	char	*value;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	val_env = ft_substr(line, 0, i);
	value = ft_strjoin(val_env, "=\0");
	free(val_env);
	val_env = NULL;
	return (value);
}

int		get_env_value(t_str *str, char *value)
{
	t_list	*tmp_env;
	size_t	len;

	tmp_env = g_shell.env;
	len = ft_strlen(value);
	while (tmp_env != NULL)
	{
		if (ft_strnstr(tmp_env->content, value, len) != NULL)
		{
			str->new_env = ft_strdup(tmp_env->content + len);
			return (0);
		}
		tmp_env = tmp_env->next;
	}
	str->new_env = ft_strdup("\0");
	return (0);
}

int		add_env_value(t_str *str)
{
	char	*tmp_arg;
	int		size;

	tmp_arg = str->new_arg;
	size = str->size_arg - ft_strlen(tmp_arg);
	str->new_arg = ft_strjoin(tmp_arg, str->new_env);
	str->new_env = (char *)simple_free(str->new_env);
	str->i_arg = ft_strlen(str->new_arg);
	str->new_arg[str->i_arg] = 0;
	if (size > 0)
		str->new_arg = ft_realloc(str->new_arg, size + 1);
	str->size_arg = str->i_arg + size;
	tmp_arg = (char *)simple_free(tmp_arg);
	return (str->i_arg);
}

int		parser_env(char *line, t_str *str)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	if (line[0] == '?')
	{
		value = ft_itoa(g_shell.err);
		str->new_env = ft_strdup(value);
	}
	if (ft_isdigit(line[0]))
		str->new_env = ft_strdup("\0");
	if (line[0] == '_' || ft_isalpha(line[0]))
	{
		value = get_env_name(line);
		get_env_value(str, value);
		i += ft_strlen(value) - 1;
	}
	else
		i++;
	value = (char *)simple_free(value);
	return (i);
}
