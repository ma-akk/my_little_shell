/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:37:47 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/18 19:39:22 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_init_hist(char *path, t_doblist *tmp, int ret, int fd)
{
	char	*line;

	if (path == NULL)
		path = getcwd(path, 10000);
	g_shell.path_hist = ft_strjoin(path, "/.history");
	free(path);
	if ((fd = open(g_shell.path_hist, O_CREAT | O_RDWR | O_APPEND, 0600)) == -1)
		return (2);
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret == -1 || !line)
			return (3);
		if (line != NULL && (ft_strlen(line) == 0))
			free(line);
		else if (line != NULL && (ft_strlen(line) != 0))
			tmp = ft_doblstnew(line);
		if (line != NULL && (ft_strlen(line) != 0) && g_shell.hist == NULL)
			g_shell.hist = tmp;
		else if (line != NULL && ft_strlen(line) != 0)
			ft_doblstadd_front(&g_shell.hist, tmp);
	}
	close(fd);
	return (0);
}

static int		ft_shlvl(char *shlvl, int i, char *tmp)
{
	if (shlvl == NULL || !ft_allisdigit(shlvl))
	{
		if (shlvl)
			free(shlvl);
		return (ft_insert_arg("SHLVL=1"));
	}
	i = ft_atoi(shlvl);
	i++;
	free(shlvl);
	if (i == 1000)
		return (ft_insert_arg("SHLVL="));
	else if (i > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(i, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		return (ft_insert_arg("SHLVL=1"));
	}
	tmp = ft_itoa(i);
	shlvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	tmp = NULL;
	ft_insert_arg(shlvl);
	free(shlvl);
	return (0);
}

static int		ft_init_help(void)
{
	g_shell.err = 0;
	g_shell.args = NULL;
	g_shell.hist = NULL;
	g_shell.true_fd[0] = dup(0);
	g_shell.true_fd[1] = dup(1);
	g_shell.sig_fl = S_NONE;
	ft_insert_arg("OLDPWD");
	return (0);
}

int				ft_init_shell(char **env, int i)
{
	t_list		*tmp;
	t_doblist	*tmpb;
	char		*path;
	char		*shlvl;

	path = NULL;
	shlvl = NULL;
	while (env != NULL && env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			path = ft_strdup(env[i] + 5);
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			shlvl = ft_strdup(env[i] + 6);
		if (!(tmp = ft_lstnew(ft_strdup(env[i]))))
			return (1);
		if (i == 0)
			g_shell.env = tmp;
		else
			ft_lstadd_back(&g_shell.env, tmp);
	}
	tmpb = NULL;
	ft_shlvl(shlvl, 0, path);
	ft_init_help();
	return (ft_init_hist(path, tmpb, 1, 0));
}
