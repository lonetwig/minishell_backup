/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:42:22 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/14 14:16:22 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	compare_oper(char *str, int *i, int oper[2])
{
	int	oper_i;

	if(oper[0])
		oper_i = 1;
	else if (oper[1])
		oper_i = 2;
	else
		oper_i = 0;
	if ((*str == '<' && *(str + 1) == '<') || \
	(*str == '>' && *(str + 1) == '>'))
		return ((*i)++, oper[oper_i] = 1, 1);
	if (*str == '<' || *str == '>')
		return (oper[oper_i] = 1, 1);
	if ((*str == '|' && *(str + 1) == '|') || \
	(*str == '&' && *(str + 1) == '&'))
		return ((*i)++,oper[oper_i] = 2, 2);
	if (*str == '|')
		return (oper[oper_i] = 2, 2);
	return (0);
}

void	check_opers(char *str)
{
	int				i;
	static int		oper[3];
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		if (str[i] == ' ' && ++i)
			continue ;
		if (!compare_oper(str + i, &i, oper) || c_q.is_dq || c_q.is_sq)
			(oper[0] = 0, oper[1] = 0);
		if (oper[2] || (oper[1] && oper[0] - oper[1] <= 0))
			exit(1);
		i++;
	}
	if (oper[0] || oper[1])
		exit(1);
}
