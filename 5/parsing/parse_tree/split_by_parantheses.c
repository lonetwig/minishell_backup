/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_parantheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:57:04 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/21 13:07:37 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	check_str(char *str)
{
	int				i;
	int				p_i;
	t_check_quote	c_q;

	i = 0;
	p_i = 0;
	c_q = (t_check_quote){0};
	while (str[i] == ' ')
		i++;
	if (str[i] != '(')
		exit(1);
	while (str[i])
	{
		check_parentheses(str[i], &p_i);
		check_quotes(str[i], &c_q);
		// printf("%c \n", str[i]);
		if (str[i] == ')' && !cond_q(c_q) && !p_i)
			break ;
		i++;
	}
	i++;
	while (str[i] == ' ')
		i++;
	// printf("%s (%s)\n",str, str + i);
	if (str[i] && str[i] != ')')
		exit(1);
}

static int	get_para_size(char *str)
{
	int				i;
	int				size;
	int				p_i;
	t_check_quote	c_q;

	i = 0;
	size = 0;
	p_i = 0;
	c_q = (t_check_quote){0};
	while (str[i] == ' ')
		i++;
	i++;
	while (str[i])
	{
		check_parentheses(str[i], &p_i);
		check_quotes(str[i], &c_q);
		i++;
		size++;
		if (str[i] == ')' && !cond_q(c_q) && !p_i)
			break ;
	}
	if (size == 0)
		exit(1);
	return (size);
}

char	*split_by_parantheses(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	check_str(str);
	new_str = malloc (get_para_size(str) + 1);
	// printf("%d---\n", get_para_size(str));
	if (!new_str)
		exit(1);
	while (str[i] == ' ')
		i++;
	i++;
	while (j < get_para_size(str))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	printf("{%s %d}\n",new_str, get_para_size(str));

	return (new_str);
}