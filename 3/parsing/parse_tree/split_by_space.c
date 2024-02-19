/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:24:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/19 15:22:02 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	count_arr_length(char *s)
{
	int				count;
	t_check_quote	c_q;
	int				c_p;
	int				i;

	count = 0;
	i = 0;
	c_p = 0;
	c_q = (t_check_quote){0};
	check_quotes(s[i], &c_q);
	check_parentheses(s[i], &c_p);
	if (s[i] && s[i] != ' ')
		count++;
	i++;
	while (*s && s[i] && s[i - 1])
	{
		if (!cond_space(s, i) && cond_space(s, i - 1) && !cond_q(c_q) && !c_p)
			count++;
		check_quotes(s[i], &c_q);
		check_parentheses(s[i], &c_p);
		i++;
	}
	return (count);
}

char	**split_by_space(char *s)
{
	t_split	all;

	all.str = s;
	all.c_q = (t_check_quote){0};
	all.c_p = 0;
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
