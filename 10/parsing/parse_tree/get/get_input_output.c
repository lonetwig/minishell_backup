/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:29 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/04 14:37:04 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	ambiguity(char *str, char **next_str, char *pre, char **err)
{
	char	**arr;
	int		is_diffrent;

	is_diffrent = ft_strcmp(*next_str, pre);
	if (!(cond_oper(str, INPUT) || cond_oper(str, OUTPUT) || \
	cond_oper(str, APPEND)))
		return (0);
	arr = split_by_space(*next_str, err);
	if (arr && arr[0])
		*next_str = arr[0];
	if (arr && arr[1])
		return (*err = "Minibash: ambiguous redirect\n", 1);
	get_environment(&pre, err);
	arr = split_by_space(pre, err);
	if (arr && arr[1])
		return (*err = "Minibash: ambiguous redirect\n", 1);
	return (0);
}

static void	move_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!arr[i + 1])
			arr[i] = NULL;
		arr[i] = arr[i + 1];
		i++;
	}
}

static int	open_file(char *str, int oper_size, int expected, char **err)
{
	int	fd;
	int	flags;

	if (expected == 0)
		fd = ft_open(str, OPEN_READ, err, 0);
	else if (expected == 1)
	{
		if (oper_size == 1)
			fd = ft_open(str, OPEN_TRUNC, err, 0);
		else if (oper_size == 2)
			fd = ft_open(str, OPEN_APPEND, err, 0);
	}
	return (fd);
}

static int	check_if_output(char **arr, int *pre_fd, int expected, char **err)
{
	int	oper_size;
	int	fd;
	int	cnd_oper_type;

	fd = expected;
	if (expected)
		cnd_oper_type = cond_oper(*arr, OUTPUT) || cond_oper(*arr, APPEND);
	else
		cnd_oper_type = cond_oper(*arr, INPUT);
	oper_size = cond_redirect(*arr);
	if (oper_size && cnd_oper_type)
		fd = open_file(arr[1], oper_size, expected, err);
	if (*pre_fd != fd && *pre_fd != expected && fd != expected)
		ft_open(NULL, 0, NULL, *pre_fd);
	if (fd > expected || cond_oper(*arr, H_DOC))
	{
		move_cmd(arr);
		move_cmd(arr);
	}
	return (fd);
}

int	get_input_output(char **arr, int expected, char** pre, char **err)
{
	int	i;
	int	fd;
	int	final_fd;

	i = 0;
	final_fd = expected;
	if ((cond_oper(arr[i], INPUT) || cond_oper(arr[i], OUTPUT) || \
	cond_oper(arr[i], APPEND)) && !arr[i + 1])
		return (arr[i] = NULL, expected);
	while (arr[i] && arr[i + 1])
	{
		if (*err || (ambiguity(arr[i], arr + i + 1, pre[i + 1], err) && ++i))
			return (expected) ;
		if (pre && cond_redirect(arr[i]) && !cond_redirect(pre[i]) && ++i)
			continue ;
		fd = check_if_output(arr + i, &final_fd, expected, err);
		if (fd == -1)
			return (expected);
		if (fd != expected)
			(pre += 2 , final_fd = fd);
		if (fd == expected)
			i++;
	}
	return (final_fd);
}
