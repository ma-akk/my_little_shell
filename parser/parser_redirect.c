/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:47:13 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/26 16:47:32 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

int	parser_filename(char *line, t_str *str)
{
	int i;

	i = 0;
	while (line[i] != '\0' && !ft_strchr(SEPARAT, line[i]))
		i = parser_new_arg(line, str, i);
	str->new_arg[str->i_arg] = '\0';
	return (i);
}

int	def_redi(t_pars *pars, char *filename, t_arg *args)
{
	int fd;

	fd = open(filename, O_RDONLY, 0444);
	if (fd < 0)
		return (curerror_exit(5, strerror(errno), filename));
	pars->file_in = (char *)simple_free(pars->file_in);
	pars->file_in = filename;
	args->fl |= F_REDI;
	close(fd);
	return (0);
}

int	def_redt(t_pars *pars, char *filename, t_arg *args)
{
	int fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (curerror_exit(5, strerror(errno), filename));
	pars->file_out = (char *)simple_free(pars->file_out);
	pars->file_out = filename;
	args->fl = (args->fl | F_REDT) & (~F_REDA);
	close(fd);
	return (0);
}

int	def_reda(t_pars *pars, char *filename, t_arg *args)
{
	int fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (curerror_exit(5, strerror(errno), filename));
	pars->file_out = (char *)simple_free(pars->file_out);
	pars->file_out = filename;
	args->fl = (args->fl | F_REDA) & (~F_REDT);
	close(fd);
	return (0);
}

int	parser_red(char *line, t_pars *pars, t_arg *args)
{
	int		i;
	t_str	red_name;

	i = 1;
	if (line[0] == '>' && line[1] == '>')
		i = 2;
	i += skip_space(line + i);
	init_str(&red_name, ft_strlen(line + i));
	i += parser_filename(line + i, &red_name);
	if (line[0] == '>' && line[1] == '>')
		if (def_reda(pars, red_name.new_arg, args))
			return (-1);
	if (line[0] == '>' && line[1] != '>')
		if (def_redt(pars, red_name.new_arg, args))
			return (-1);
	if (line[0] == '<')
		if (def_redi(pars, red_name.new_arg, args))
			return (-1);
	red_name.new_arg = NULL;
	return (i);
}
