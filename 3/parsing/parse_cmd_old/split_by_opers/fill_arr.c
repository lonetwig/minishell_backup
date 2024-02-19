/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:26:44 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/13 11:01:46 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minibash.h"

static int	str_size(t_split *all, int s_i)
{
	int	i;

	i = s_i;
	while (all->str[i])
	{
		check_quotes(all->str[i], &(all->c_q));
		if (check_delim(all->str[i]) && !all->c_q.is_dq && !all->c_q.is_sq)
			return (i);
		i++;
	}
	return (i);
}

static void	fill_str(t_split *all, char *dst, int *s_i)
{
	int	i;

	i = *s_i;
	all->c_q = (t_check_quote){0};
	while (all->str[i] && (!check_delim(all->str[i]) || \
	(all->c_q.is_dq || all->c_q.is_sq)))
	{
		check_quotes(all->str[i], &(all->c_q));
		*dst = all->str[i];
		dst++;
		i++;
		(*s_i)++;
	}
	*dst = '\0';
}

static void	add_str_to_arr(t_split *all, int *s_i)
{
	static int	arr_i = 0;

	all->arr[arr_i] = malloc(str_size(all, *s_i) + 1);
	if (all->arr[arr_i] == NULL)
        exit(1);
	fill_str(all, all->arr[arr_i], s_i);
	arr_i++;
}	

int	fill_arr(t_split *all)
{
	int	s_i;

	s_i = 0;
	if (all->str[s_i] && !check_delim(all->str[s_i]))
		add_str_to_arr(all, &s_i);
	s_i++;
	while (all->str[s_i])
	{
		if (!check_delim(all->str[s_i]) && check_delim(all->str[s_i - 1]))
			add_str_to_arr(all, &s_i);
		s_i++;
	}
	return (1);
}
