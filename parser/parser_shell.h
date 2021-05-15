/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 21:19:55 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/31 21:32:30 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_SHELL_H
# define PARSER_SHELL_H
# include "../minishell.h"
# define SEPARAT "<> |;"

typedef struct	s_str
{
	int		i_arg;
	int		size_arg;
	char	*new_arg;
	char	*new_env;
}				t_str;

typedef struct	s_pars
{
	int		count_struct;
	int		count_arg;
	char	*file_out;
	char	*file_in;
	t_str	*str;
}				t_pars;

t_arg			**args_alloc(t_pars *pars);
void			args_free(t_pars *pars);
void			pars_free(t_pars *pars);
void			struct_free(t_arg *args);
void			*simple_free(void *ptr);
int				synerror_exit(int code, char *err);
int				curerror_exit(int code, char *err, char *filename);
int				memerror_exit(int code, char *err);
void			init_pars(t_pars *pars);
void			init_str(t_str *str, int size);
int				check_syntax(char *line);
int				err_endoffile(char *line, int *i);
int				err_quotes(char *line, int i, int j);
int				err_ut_newline(char *line, int i);
int				err_ut_before(char *line, int i);
int				err_ut_after(char *line, int i);
int				parser_sin_quotes(char *line, t_str *str);
int				parser_doub_quotes(char *line, t_str *str);
int				parser_shield(char *line, char fl);
int				parser_env(char *line, t_str *str);
int				get_env_value(t_str *str, char *value);
char			*get_env_name(char *line);
int				add_env_value(t_str *str);
int				parser_red(char *line, t_pars *pars, t_arg *args);
int				parser_filename(char *line, t_str *str);
int				def_redi(t_pars *pars, char *filename, t_arg *args);
int				def_redt(t_pars *pars, char *filename, t_arg *args);
int				def_reda(t_pars *pars, char *filename, t_arg *args);
int				check_count_struct(char *line, t_pars *pars);
int				input_arg(char *line, t_pars *pars, t_arg *args);
int				input_fl(t_arg *cur_args, t_pars *pars);
int				add_arg(char *line, t_pars *pars);
int				check_count_arg(char *line, t_pars *pars);
int				skip_shield(char *line);
int				skip_quotes(char *line);
int				skip_space(char *line);
int				skip_red(char *line);
int				parser_start(char *line);
int				parser_sim(char *line, t_str *str);
int				parser_new_arg(char *line, t_str *str, int i);
int				parser_arg(char *line, t_pars *pars, t_arg *args);
char			*pre_parser_env(char *line);
int				input_new_line(char *line, t_str *arg_env, int i);

int				skip_cur_struct(char *line);

#endif
