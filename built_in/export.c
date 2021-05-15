/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:45:55 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 20:45:58 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_sort_help(char **s_arr, int *left, int *right)
{
	char *tmp;

	if (*left <= *right)
	{
		tmp = s_arr[*left];
		s_arr[*left] = s_arr[*right];
		s_arr[*right] = tmp;
		(*left)++;
		(*right)--;
	}
}

void		ft_qsort(char **s_arr, int first, int last)
{
	int		left;
	int		right;
	char	*middle;

	if (first < last)
	{
		left = first;
		right = last;
		middle = s_arr[(left + right) / 2];
		while (left <= right)
		{
			while (ft_strncmp(s_arr[left], middle, ft_strlen(middle)) < 0)
				left++;
			while (ft_strncmp(s_arr[right], middle, ft_strlen(middle)) > 0)
				right--;
			ft_sort_help(s_arr, &left, &right);
		}
		ft_qsort(s_arr, first, right);
		ft_qsort(s_arr, left, last);
	}
}

static int	ft_export_error(char *str, char *s_arr)
{
	int		l;
	char	s[2];

	s[0] = 34;
	s[1] = '\0';
	if (s_arr == NULL)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	l = ft_strchr_i(str, '=');
	if (l == -1)
		ft_strlcat(s_arr, str, ft_strlen(str) + ft_strlen(s_arr) + 1);
	else
	{
		ft_strlcat(s_arr, str, 13 + l);
		ft_strlcat(s_arr, s, 15 + l);
		ft_strlcat(s_arr, ft_strchr(str, '=') + 1, 15 + l + ft_strlen(str));
		ft_strlcat(s_arr, s, 17 + l + ft_strlen(str));
	}
	return (0);
}

static int	ft_export_sort(int l)
{
	char	**s_arr;
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = g_shell.env;
	s_arr = (char **)malloc(sizeof(char *) * (l + 1));
	while (++i < l)
	{
		s_arr[i] = (char *)malloc(sizeof(char) *
			(ft_strlen(tmp->content) + 15));
		ft_strlcat(s_arr[i], "declare -x ", 12);
		ft_export_error(tmp->content, s_arr[i]);
		tmp = tmp->next;
	}
	s_arr[i] = NULL;
	ft_qsort(s_arr, 0, i - 1);
	i = -1;
	while (s_arr[++i] != NULL)
		ft_putendl(s_arr[i]);
	i = -1;
	while (s_arr[++i] != NULL)
		free(s_arr[i]);
	free(s_arr);
	return (0);
}

int			ft_export(char **arg)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	if (arg != NULL && arg[1] == NULL)
		return (ft_export_sort(ft_lstsize(g_shell.env)));
	while (arg != NULL && arg[++i] != NULL)
	{
		if (ft_isalpha(arg[i][0]) == 0 && arg[i][0] != '_')
			ret = ft_export_error(arg[i], NULL);
		else
			ret = 0;
		j = 0;
		while (arg[i][++j] != '\0' && arg[i][j] != '=' && !ret)
		{
			if (ft_isalnum(arg[i][j]) == 0 && arg[i][j] != '_')
				ret = ft_export_error(arg[i], NULL);
			else
				ret = 0;
		}
		if (ret == 0)
			ft_insert_arg(arg[i]);
	}
	return (ret);
}
