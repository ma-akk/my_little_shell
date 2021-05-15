/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtresa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:54:25 by gtresa            #+#    #+#             */
/*   Updated: 2021/03/30 20:54:33 by gtresa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_shell.h"

void	init_pars(t_pars *pars)
{
	pars->count_struct = 1;
	pars->count_arg = 0;
	pars->file_out = NULL;
	pars->file_in = NULL;
	pars->str = (t_str *)malloc(sizeof(t_str));
}

void	init_str(t_str *str, int size)
{
	str->i_arg = 0;
	str->size_arg = size;
	str->new_arg = (char *)ft_calloc(size + 1, sizeof(char));
	str->new_env = NULL;
}
