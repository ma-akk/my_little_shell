/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:46:13 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:46:15 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_insert_arg(char *arg)
{
	int		j;
	t_list	*tmp;

	tmp = g_shell.env;
	while (tmp)
	{
		j = ft_strlen_m(tmp->content, '=');
		if (ft_strncmp(arg, tmp->content, j) == 0 && ft_strlen_m(arg, '=') == j)
		{
			tmp->content = ft_realloc(tmp->content, ft_strlen(arg) + 2);
			if ((j = ft_strchr_i(arg, '=')) != -1)
			{
				ft_strlcpy(tmp->content + j, "=", 2 + ft_strlen(tmp->content));
				ft_strlcpy(tmp->content + j + 1, arg + ft_strchr_i(arg, '=')
				+ 1, ft_strlen(arg) + ft_strlen(tmp->content) + 2);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&g_shell.env, ft_lstnew(ft_strdup(arg)));
	return (0);
}

int			ft_cd_exp(char *oldpwd)
{
	char *arg;
	char pwd[10000];

	arg = ft_strjoin("OLDPWD=", oldpwd);
	ft_insert_arg(arg);
	free(arg);
	if (getcwd(pwd, 10000) == NULL)
		arg = ft_strjoin("PWD=", oldpwd);
	else
		arg = ft_strjoin("PWD=", pwd);
	ft_insert_arg(arg);
	free(arg);
	return (0);
}

int			ft_cd_home(char *oldpwd, t_list *tmp, char *home)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
			home = ft_strdup(tmp->content + 5);
		tmp = tmp->next;
	}
	if (home == NULL)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	if (home == NULL)
		return (1);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(home);
		return (errno);
	}
	else
		ft_cd_exp(oldpwd);
	free(home);
	return (0);
}

int			ft_cd(char **arg)
{
	char	oldpwd[10000];
	t_list	*tmp;
	char	*home;

	getcwd(oldpwd, 10000);
	tmp = g_shell.env;
	home = NULL;
	if (arg[1] != NULL)
	{
		if (chdir(arg[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (errno);
		}
		else
			ft_cd_exp(oldpwd);
	}
	else
		return (ft_cd_home(oldpwd, tmp, home));
	return (0);
}
