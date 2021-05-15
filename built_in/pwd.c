/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:17:57 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/19 15:18:13 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pwd(void)
{
	char	*dir;
	t_list	*tmp;

	tmp = g_shell.env;
	dir = NULL;
	dir = getcwd(dir, 10000);
	if (dir == NULL)
	{
		while (tmp)
		{
			if (ft_strncmp("OLDPWD=", tmp->content, 7) == 0)
				dir = ft_strdup(tmp->content + 7);
			tmp = tmp->next;
		}
		ft_putendl(dir);
		if (dir != NULL)
			free(dir);
		return (errno);
	}
	ft_putendl(dir);
	free(dir);
	return (0);
}
