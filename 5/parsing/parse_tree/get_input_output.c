/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:29 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/23 17:25:40 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	free_cmds(char **arr)
{
	while (*arr)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
}

static void	move_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (i == 0)
			free(arr[i]);
		if (!arr[i + 1])
			arr[i] = NULL;
		arr[i] = arr[i + 1];
		i++;
	}
}

static int	open_file(char *str, int oper_size, int expected)
{
	int	fd;
	int	flags;

	if (expected == 0)
		flags = O_RDONLY;
	else if (expected == 1)
	{
		if (oper_size == 1)
			flags = O_CREAT | O_TRUNC | O_WRONLY;
		else if (oper_size == 2)
			flags = O_CREAT | O_APPEND | O_WRONLY;
	}
	if (oper_size == 1)
		fd = open(str, flags, 0777);
	else if (oper_size == 2)
		fd = open(str, flags, 0777);
	return (fd);
}

static int	check_if_output(char **arr, int *pre_fd, int i, int expected)
{
	int	oper_size;
	int	fd;
	int	cnd_oper_type;

	fd = expected;
	if (expected)
		cnd_oper_type = cond_oper(arr[i], OUTPUT) || cond_oper(arr[i], APPEND);
	else
		cnd_oper_type = cond_oper(arr[i], INPUT);
	oper_size = cond_redirect(arr[i]);
	if (oper_size && cnd_oper_type)
		fd = open_file(arr[i + 1], oper_size, expected);
	if (*pre_fd != fd && *pre_fd != expected && fd != expected)
		close(*pre_fd);
	if (fd > expected || cond_oper(arr[i], H_DOC))
	{
		move_cmd(arr + i);
		move_cmd(arr + i);
	}
	return (fd);
}

int	get_input_output(char **arr, int expected)
{
	int	i;
	int	fd;
	int	final_fd;

	i = 0;
	final_fd = expected;
	while (arr[i + 1])
	{
		fd = check_if_output(arr, &final_fd, i, expected);
		if (fd == -1)
		{
			free_cmds(arr);
			return (expected);
		}
		if (fd != expected)
			final_fd = fd;
		if (fd == expected)
			i++;
	}
	return (final_fd);
}
