/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:46:56 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:46:58 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int			ft_unset(char **arg, int i, int ret)
{
	int		j;
	t_list	*tmp;

	while (arg[++i] != NULL && !(j = 0))
	{
		tmp = g_shell.env;
		if (ft_isalpha(arg[i][j]) == 0 && arg[i][j] != '_')
			ret = ft_unset_error(arg[i]);
		if (ft_isalpha(arg[i][j]) == 0 && arg[i][j] != '_')
			break ;
		while (arg[i][++j] != '\0')
			if (ft_isalnum(arg[i][j]) == 0 && arg[i][j] != '_')
			{
				ret = ft_unset_error(arg[i]);
				break ;
			}
		while (tmp)
		{
			if (!ft_strncmp(tmp->content, arg[i],
(j = ft_strlen_m(tmp->content, '='))) && ft_strlen_m(arg[i], '=') == j)
				g_shell.env = ft_lstdelnote(g_shell.env, tmp, free);
			tmp = tmp->next;
		}
	}
	return (ret);
}
