/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:29 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 14:43:44 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

// static void	free_cmds(char **arr)
// {
// 	while (*arr)
// 	{
// 		free(*arr);
// 		*arr = NULL;
// 		arr++;
// 	}
// }

static void	move_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		// if (i == 0)
		// 	free(arr[i]);
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
	while (arr[i] && arr[i + 1])
	{
		if (pre && cond_redirect(arr[i]) && !cond_redirect(pre[i]) && ++i)
			continue ;
		fd = check_if_output(arr + i, &final_fd, expected, err);

		if (fd == -1)
			return (expected);
		if (fd != expected)
		{
			if (pre)
				pre += 2;
			final_fd = fd;
		}
		if (fd == expected)
			i++;
	}
	return (final_fd);
}
