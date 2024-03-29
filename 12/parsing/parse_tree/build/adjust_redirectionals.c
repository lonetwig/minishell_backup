/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_redirectionals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 08:46:11 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static char	*append_space(char *str, int i, int oper_size, char **error)
{
	int		j;
	char	*new_str;

	j = 0;
	new_str = ft_malloc(ft_strlen(str) + 1 + oper_size, 0, error);
	if (!new_str)
		return (NULL);
	while (j < i)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = ' ';
	j++;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*adjust_redirectionals(char *str, char **error)
{
	int				i;
	int				oper_size;
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	while (str[i])
	{
		check_quotes(str[i], &c_q);
		oper_size = cond_redirect(str + i);
		if (!cond_q(c_q) && i != 0 && oper_size && str[i - 1] != ' ' && i++)
			str = append_space(str, i - 1, oper_size, error);
		if (!cond_q(c_q) && oper_size && str[i + oper_size] != ' ')
			str = append_space(str, i + oper_size, oper_size, error);
		if (str == NULL)
			return (NULL);
		if (oper_size)
			i+= oper_size;
		else
			i++;
	}
	return (str);
}
