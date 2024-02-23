/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:24:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/19 16:33:02 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	str_size(t_split *all, int s_i)
{
	int		i;
	int		size;
	char	*str;

	i = s_i;
	size = 0;
	str = all->str;
	while (all->str[i])
	{
		check_quotes(str[i], &(all->c_q));
		check_parentheses(str[i], &(all->c_p));
		if (cond_space(str, i) && !cond_q(all->c_q) && !all->c_p)
			return (size);
		if (!cond_jump_quote(str[i], all->c_q))
			size++;
		i++;
	}
	return (size);
}

static void	fill_str(t_split *all, char *dst, int *s_i)
{
	int		i;
	char	*str;

	i = *s_i;
	str = all->str;
	all->c_q = (t_check_quote){0};
	while ((str[i] && !cond_space(str, i)) || cond_q(all->c_q) || all->c_p)
	{
		check_quotes(str[i], &(all->c_q));
		check_parentheses(str[i], &(all->c_p));
		if (!cond_jump_quote(str[i], all->c_q))
		{
			*dst = str[i];
			dst++;
		}
		i++;
		(*s_i)++;
	}
	*dst = '\0';
}

static void	add_str_to_arr(t_split *all, int *s_i, int arr_i)
{
	all->arr[arr_i] = malloc(str_size(all, *s_i) + 1);
	if (all->arr[arr_i] == NULL)
        exit(1);
	fill_str(all, all->arr[arr_i], s_i);
	arr_i++;
}

int	fill_arr(t_split *all)
{
	int		s_i;
	int		arr_i;
	char	*str;

	s_i = 0;
	arr_i = 0;
	str = all->str;
	all->c_q = (t_check_quote){0};
	check_quotes(str[s_i], &(all->c_q));
	check_parentheses(str[s_i], &(all->c_p));
	if (str[s_i] && str[s_i] != ' ')
		add_str_to_arr(all, &s_i, arr_i++);
	s_i++;
	while (all->str[s_i])
	{
		if (!cond_space(str, s_i) && cond_space(str, s_i - 1) && \
		!cond_q(all->c_q) && !all->c_p)
			add_str_to_arr(all, &s_i, arr_i++);
		check_quotes(str[s_i], &(all->c_q));
		check_parentheses(str[s_i], &(all->c_p));
		s_i++;
	}
	return (1);
}
