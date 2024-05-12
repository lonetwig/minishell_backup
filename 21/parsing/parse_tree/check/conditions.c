/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:08:42 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/12 12:35:50 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

//used to check if you are either inside single quotes or double quotes
//in case of inside quotes it returns 1
int	cond_q(t_check_quote c_q)
{
	if (c_q.is_dq || c_q.is_sq)
		return (1);
	return (0);
}

//used to check if current character in string is space
//in case of space it returns 1
int	cond_space(char *str, int i)
{
	if (str[i] == ' ')
		return (1);
	return (0);
}

// used to check if the quote is literal, either single or double.
// in case of being literal it returns 0
int	cond_jump_quote(char c, t_check_quote c_q)
{
	if (c == '\'' && !c_q.is_dq)
		return (1);
	if (c == '\"' && !c_q.is_sq)
		return (1);
	return (0);
}

//used to check if an oper exists of not (including redirectionals)
//in case of finding it, it returns the found oper enum
int	cond_oper(char *str, t_e_oper oper)
{
	if ((*str == '<' && *(str + 1) == '<') && (oper == H_DOC || oper == NONE))
		return (H_DOC);
	if ((*str == '<' && *(str + 1) != '<') && (oper == INPUT || oper == NONE))
		return (INPUT);
	if ((*str == '>' && *(str + 1) == '>') && (oper == APPEND || oper == NONE))
		return (APPEND);
	if ((*str == '>' && *(str + 1) != '>') && (oper == OUTPUT || oper == NONE))
		return (OUTPUT);
	if ((*str == '|' && *(str + 1) == '|') && (oper == OR || oper == NONE))
		return (OR);
	if ((*str == '|' && *(str + 1) != '|') && (oper == PIPE || oper == NONE))
		return (PIPE);
	if ((*str == '&' && *(str + 1) == '&') && (oper == AND || oper == NONE))
		return (AND);
	return (NONE);
}

// used to check if a redirectional exists
//in case of finding it, it returns its size
int	cond_redirect(char *str)
{
	if (!str)
		return (0);
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	if (*str == '<' && *(str + 1) == '<')
		return (2);
	if (*str == '<' && *(str + 1) != '<')
		return (1);
	if (*str == '>' && *(str + 1) != '>')
		return (1);
	return (0);
}
