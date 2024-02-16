/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:28:22 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/16 13:07:47 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static e_oper	find_oper(char c, char next_c)
{
	if (c == '|' && next_c == '|')
		return (OR);
	if (c == '&' && next_c == '&')
		return (AND);
	if (c == '|')
		return (PIPE);
	if (c == '<' && next_c == '<')
		return (H_DOC);
	if (c == '>' && next_c == '>')
		return (APPEND);
	if (c == '<')
		return (INPUT);
	if (c == '>')
		return (OUTPUT);
	return (NONE);
}

static e_oper	split_cmds(char *s, char ***l_r, e_oper wanted)
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
		if (oper == wanted && i_p == 0 && !c_q.is_dq && !c_q.is_sq)
		{
			*l_r = split_by_oper(s, oper, (char[2]){s[i], s[i + 1]});
			return (oper);
		}
		i++;
	}
	return (NONE);
}

e_oper	split_cmds_queue(char *s, char ***left_right)
{
	int		*oper_arr;
	e_oper	oper_found;
	int		i;

	oper_arr = (int []){OR, AND, PIPE, INPUT, OUTPUT, H_DOC, APPEND, NONE};
	i = 0;
	while (oper_arr[i])
	{
		oper_found = split_cmds(s, left_right, oper_arr[i]);
		if (oper_found)
			return (oper_found);
		i++;
	}
	*left_right = malloc(sizeof(char *) * 2);
	if (!left_right)
		exit(1);
	(*left_right)[0] = s;
	(*left_right)[1] = NULL;
	return (NONE);
}
