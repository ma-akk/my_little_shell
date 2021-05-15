/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:45:25 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:45:28 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_env(char **arg, int i)
{
	t_list *tmp;

	if (arg[1] == NULL)
	{
		tmp = g_shell.env;
		while (tmp)
		{
			if (ft_strchr(tmp->content, '=') != NULL)
				ft_putendl(tmp->content);
			tmp = tmp->next;
		}
	}
	else
		ft_pult(arg + 1, i, 0);
	return (0);
}
