/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:08:42 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/16 10:34:40 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

int	cond_q(t_check_quote c_q)
{
	if (c_q.is_dq || c_q.is_sq)
		return (1);
	return (0);
}

int	cond_space(char *str, int i)
{
	if (str[i] == ' ')
		return (1);
	return (0);
}

int	cond_jump_quote(char c, t_check_quote c_q)
{

	if (c == '\'' && !c_q.is_dq)
		return (1);
	if (c == '\"' && !c_q.is_sq)
		return (1);
	return (0);
}

int	cond_oper(char *str, e_oper oper)
{
	if ((*str == '<' && *(str + 1) == '<') && oper == H_DOC)
		return (H_DOC);
	if ((*str == '<' && *(str + 1) != '<') && oper == INPUT)
		return (INPUT);
	if ((*str == '>' && *(str + 1) == '>') && oper == APPEND)
		return (APPEND);
	if ((*str == '>' && *(str + 1) != '>') && oper == OUTPUT)
		return (OUTPUT);
	if ((*str == '|' && *(str + 1) == '|') && oper == OR)
		return (OR);
	if ((*str == '|' && *(str + 1) != '|') && oper == PIPE)
		return (PIPE);
	if ((*str == '&' && *(str + 1) == '&') && oper == AND)
		return (AND);
	return (NONE);
}