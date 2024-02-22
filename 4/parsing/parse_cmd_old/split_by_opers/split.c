/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:26:44 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/21 12:29:59 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minibash.h"

int	check_delim(char c)
{
	char	*delim;

	delim = "|<>";
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

static int	count_arr_length(char *s)
{
	int				count;
	t_check_quote	c_q;
	int				i;

	count = 0;
	i = 0;
	c_q = (t_check_quote){0};
	check_quotes(s[i], &c_q);
	if (s[i] && !check_delim(s[i]))
		count++;
	i++;
	while (*s && s[i] && s[i - 1])
	{
		if (!check_delim(s[i]) && check_delim(s[i - 1]) && \
		!c_q.is_dq && !c_q.is_sq)
			count++;
		check_quotes(s[i], &c_q);
		i++;
	}
	return (count);
}

char	**split_by_oper(char *s)
{
	t_split	all;

	all.str = s;
	all.c_q = (t_check_quote){0};
	all.arr_len = count_arr_length(s);
	all.arr = malloc((all.arr_len + 1) * sizeof(char *));
	if (all.arr == NULL)
		exit(1);
	all.arr[all.arr_len] = NULL;
	fill_arr(&all);
	if (all.c_q.is_dq || all.c_q.is_sq)
		exit(1);
	return (all.arr);
}

//> < >> <<
