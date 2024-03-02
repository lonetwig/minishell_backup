/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_redirectionals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 10:57:41 by ealislam         ###   ########.fr       */
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
	// free_str(str);
	return (new_str);
}

char	*adjust_redirectionals(char *str, char **error)
{
	int	i;
	int	oper_size;

	i = 0;
	while (str[i])
	{
		oper_size = cond_redirect(str + i);
		if (i != 0 && oper_size && str[i - 1] != ' ' && i++)
			str = append_space(str, i - 1, oper_size, error);
		if (oper_size && str[i + oper_size] != ' ')
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
