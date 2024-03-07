/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:28:22 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 07:51:44 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

e_oper	find_oper(char c, char next_c)
{
	if (c == '|' && next_c == '|')
		return (OR);
	if (c == '&' && next_c == '&')
		return (AND);
	if (c == '|')
		return (PIPE);
	if (c == '(')
		return (PARENTHESES);
	return (NONE);
}

static e_oper	split_cmds(char *s, char ***l_r, e_oper wanted, char **err)
{
	int				i;
	int				i_p;
	t_check_quote	c_q;
	e_oper			oper;

	i = 0;
	i_p = 0;
	c_q = (t_check_quote){0};
	while (s[i])
	{
		oper = find_oper(s[i], s[i + 1]);
		check_quotes(s[i], &c_q);
		check_parentheses(s[i], &i_p);
		if (wanted == PARENTHESES && oper == PARENTHESES && !cond_q(c_q))
			return (PARENTHESES);
		if (oper == wanted && !i_p && !cond_q(c_q))
		{
			*l_r = split_by_oper(s, oper, (char[2]){s[i], s[i + 1]}, err);
			return (oper);
		}
		i++;
	}
	return (NONE);
}

e_oper	split_cmds_queue(char *s, char ***left_right, char **error)
{
	int		*oper_arr;
	e_oper	oper_found;
	int		i;

	oper_arr = (int []){OR, AND, PIPE, PARENTHESES, NONE};
	i = 0;
	while (oper_arr[i])
	{
		oper_found = split_cmds(s, left_right, oper_arr[i], error);
		if (oper_found)
			return (oper_found);
		i++;
	}
	*left_right = ft_malloc(sizeof(char *) * 2, 0, error);
	if (!left_right)
		return (NONE);
	(*left_right)[0] = ft_strdup(s, error);
	(*left_right)[1] = NULL;
	return (NONE);
}
