/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:46:35 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/15 12:16:30 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	get_lens(char *s, e_oper oper_type, char c[2], int l_r_sizes[3])
{
	int				i;
	int				i_p;
	t_check_quote	c_q;

	i = 0;
	i_p = 0;
	c_q = (t_check_quote){0};
	while (s[i])
	{
		check_parentheses(s[i], &i_p);
		check_quotes(s[i], &c_q);
		if (s[i] == c[0] && s[i + 1] == c[1] && !i_p && !c_q.is_dq && !c_q.is_sq)
		{
			l_r_sizes[0] = i;
			if (oper_type == AND || oper_type == OR || oper_type == H_DOC || \
			oper_type == APPEND)
				l_r_sizes[1] = 2;
			else
				l_r_sizes[1] = 1;
			break ;
		}
		i++;
	}
	while (s[l_r_sizes[0] + l_r_sizes[1] + l_r_sizes[2]])
		l_r_sizes[2] += 1;
}

static void	append_str(char *str, char **arr, int size)
{
	char	*new_str;
	int	i;

	i = 0;
	new_str = malloc(size);
	if (!new_str)
		exit(1);
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	arr[0] = new_str;
}

char	**split_by_oper(char *str, e_oper oper_type, char c[2])
{
	char			**arr;
	static int		l_r_sizes[3];

	arr = malloc(3 * sizeof (char *));
	if (!arr)
		exit(1);
	get_lens(str, oper_type, c, l_r_sizes);
	append_str(str, arr, l_r_sizes[0]);
	append_str(str + l_r_sizes[0] + l_r_sizes[1], arr + 1, l_r_sizes[2]);
	arr[2] = NULL;
	return (arr);
}