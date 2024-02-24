/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_parantheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:57:04 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/24 14:06:37 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	get_fds(char *s, int *input, int *output)
{
	char	**arr;
	int		i;

	i = 0;
	arr = split_by_space(s);
	while (arr[i])
	{
		if (!arr[i + 1] || (cond_redirect(arr[i]) && \
		cond_redirect(arr[i + 1])))
			exit(1);
		i += 2;
	}
	*input = get_input_output(arr, 0, NULL);
	*output = get_input_output(arr, 1, NULL);
	free_arr(arr);
}

static void	check_end_and_get_fds(char *s, int *input, int *output)
{
	int				oper_size;
	t_check_quote	cq;
	char			*file_name;

	if (cond_oper(s, PIPE) || cond_oper(s, AND) || cond_oper(s, OR) || \
	*s == ')')
	{
		*input = 0;
		*output = 1;
		return ;
	}
	oper_size = cond_redirect(s);
	if (!s)
		exit(1);
	if (!cond_redirect(s))
	{
		*input = 0;
		*output = 1;
	}
	get_fds(s, input, output);
}

static void	check_str(char *s, int *input, int *output)
{
	int				i;
	int				p_i;
	t_check_quote	c_q;

	i = 0;
	p_i = 0;
	c_q = (t_check_quote){0};
	while (s[i] == ' ')
		i++;
	if (s[i] != '(')
		exit(1);
	while (s[i])
	{
		check_parentheses(s[i], &p_i);
		check_quotes(s[i], &c_q);
		if (s[i] == ')' && !cond_q(c_q) && !p_i)
			break ;
		i++;
	}
	i++;
	while (s[i] == ' ')
		i++;
	check_end_and_get_fds(s + i, input, output);
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

char	*split_by_parantheses(char *str, int *input, int *output)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	check_str(str, input, output);
	new_str = malloc (get_para_size(str) + 1);
	if (!new_str)
		exit(1);
	while (str[i] == ' ')
		i++;
	i++;
	while (j < get_para_size(str))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	// printf("{%s %d}\n",new_str, get_para_size(str));

	return (new_str);
}

//get output
