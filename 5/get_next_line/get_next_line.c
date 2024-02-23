/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:45:48 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/23 13:07:02 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	append_to_final_until_n(char *cur_bfr, char **fnl_str)
{
	unsigned int	f_size;
	unsigned int	c_size;
	char			*new_dst;

	f_size = get_s(*fnl_str).s_to_null;
	c_size = get_s(cur_bfr).s_to_nl;
	new_dst = malloc(c_size + f_size + 1);
	if (new_dst == NULL)
		return (1);
	str_join(cur_bfr, fnl_str, new_dst);
	return (0);
}

static int	get_remain(char **rmn, char *cur_bfr)
{
	char			*new_rmn;
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = get_s(cur_bfr).s_to_nl;
	new_rmn = malloc(get_s(cur_bfr).s_to_null - k + 1);
	if (new_rmn == NULL)
		return (1);
	while (cur_bfr[i + k])
	{
		new_rmn[i] = cur_bfr[i + k];
		i++;
	}
	new_rmn[i + get_s(*rmn).s_to_null] = '\0';
	if (*rmn)
		free(*rmn);
	*rmn = new_rmn;
	if (*rmn && !**rmn)
	{
		free(*rmn);
		*rmn = NULL;
	}
	return (0);
}

static int	trim_remain(char **remain)
{
	char				*new_remain;
	unsigned int		i;
	unsigned int		j;

	i = get_s(*remain).s_to_nl;
	j = 0;
	new_remain = malloc(get_s(*remain).s_to_null - i + 1);
	if (new_remain == NULL)
		return (1);
	while (*remain && (*remain)[i])
		new_remain[j++] = (*remain)[i++];
	new_remain[j] = '\0';
	if (*remain)
		free(*remain);
	*remain = new_remain;
	return (0);
}

static int	read_file(int fd, char **cur_buf, char **fnl_str)
{
	int	bytes_read;

	*cur_buf = malloc(BUFFER_SIZE + 1);
	if (*cur_buf == NULL)
		return (1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, *cur_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (1);
		(*cur_buf)[bytes_read] = '\0';
		if (!bytes_read)
			break ;
		if (append_to_final_until_n(*cur_buf, fnl_str))
			return (1);
		if (check_n(*cur_buf))
			break ;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*remain = NULL;
	char		*fnl_str;
	char		*cur_buf;

	fnl_str = NULL;
	cur_buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remain)
	{
		if (append_to_final_until_n(remain, &fnl_str) || \
			trim_remain(&remain))
			return (free_and_return_null(&remain, &fnl_str, &cur_buf));
		if (check_n(fnl_str))
			return (fnl_str);
	}
	if (read_file(fd, &cur_buf, &fnl_str) || \
		get_remain(&remain, cur_buf) || \
		(fnl_str && !*fnl_str))
		return (free_and_return_null(&remain, &fnl_str, &cur_buf));
	if (cur_buf)
		free (cur_buf);
	return (fnl_str);
}
