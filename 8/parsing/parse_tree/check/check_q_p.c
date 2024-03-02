/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_q_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:20:32 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/27 10:42:03 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

void	check_quotes(char c, t_check_quote *c_q)
{
	if (c == '\'' && !c_q->is_dq)
	{
		if (!c_q->is_sq)
			c_q->is_sq = 1;
		else
			c_q->is_sq = 0;
	}
	else if (c == '\"' && !c_q->is_sq)
	{
		if (!c_q->is_dq)
			c_q->is_dq = 1;
		else
			c_q->is_dq = 0;
	}
}

void	check_parentheses(char c, int *i_p)
{
	if (c == '(')
		(*i_p)++;
	if (c == ')')
		(*i_p)--;
}

void	check_q_p(char *str, char **error)
{
	int				p_counter;
	t_check_quote	c_q;

	c_q = (t_check_quote){0};
	p_counter = 0;
	while (*str)
	{
		check_quotes(*str, &c_q);
		check_parentheses(*str, &p_counter);
		str++;
	}
	if (p_counter != 0 || c_q.is_dq || c_q.is_sq)
		*error = "minbash: syntax error";
}
