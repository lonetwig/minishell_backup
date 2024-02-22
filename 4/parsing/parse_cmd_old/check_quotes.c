/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:59:47 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/13 11:01:10 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

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