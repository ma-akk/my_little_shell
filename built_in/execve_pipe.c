/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:45:06 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:45:08 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_envp(void)
{
	char	**env;
	int		i;
	int		len;
	t_list	*tmp;

	tmp = g_shell.env;
	len = ft_lstsize(g_shell.env);
	env = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (tmp)
	{
		env[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	env[++i] = NULL;
	return (env);
}

static int	ft_exe_error(int flag, char *str)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	return (errno);
}

static int	ft_exec_true(char **str, char **arg)
{
	char	*s;
	int		i;

	i = -1;
	while (str[++i] != NULL)
	{
		s = NULL;
		s = (char *)malloc(ft_strlen(str[i]) + ft_strlen(arg[0]) + 3);
		ft_strlcpy(s, str[i], ft_strlen(str[i]) + 1);
		s[ft_strlen(str[i])] = '\0';
		ft_strlcat(s, "/", ft_strlen(s) + 2);
		ft_strlcat(s, arg[0], ft_strlen(s) + ft_strlen(arg[0]) + 1);
		execve(s, arg, ft_envp());
		free(s);
	}
	exit(ft_exe_error(0, arg[0]));
	return (0);
}

int			ft_execve_pipe(char **arg)
{
	char	**str;
	t_list	*tmp;
	int		i;
	int		ret;

	tmp = g_shell.env;
	str = NULL;
	while (tmp && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (tmp)
		str = ft_split(tmp->content + 5, ':');
	i = 1;
	if (ft_strchr(arg[0], '/') || str == NULL)
	{
		if (execve(arg[0], arg, ft_envp()) == -1)
			exit(ft_exe_error(i, arg[0]));
	}
	else
		ret = ft_exec_true(str, arg);
	i = -1;
	while (str != NULL && str[++i] != NULL)
		free(str[i]);
	if (str != NULL)
		free(str);
	return (ret);
}

int			ft_pult_pipe(char **arg, int i, int err)
{
	if (arg == NULL || arg[0] == NULL)
		return (0);
	ft_redirect(0, i);
	if (!ft_strncmp("export", arg[0], 10) && ft_strlen(arg[0]) == 6)
		err = ft_export(arg);
	else if (!ft_strncmp("unset", arg[0], 10) && ft_strlen(arg[0]) == 5)
		err = ft_unset(arg, 0, 0);
	else if (!ft_strncmp("exit", arg[0], 10) && ft_strlen(arg[0]) == 4)
		err = ft_exit(arg);
	else
		err = ft_execve_pipe(arg);
	if (!(g_shell.sig_fl & S_INT) && !(g_shell.sig_fl & S_QUIT))
		g_shell.err = err;
	ft_redirect(1, i);
	return (err);
}
