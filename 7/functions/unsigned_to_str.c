/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:44 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 12:48:52 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	size_of_unsigned(unsigned int num)
{
	int	i;

	i = 0;
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	i++;
	return (i);
}

static void	unsigned_to_str2(unsigned int num, char *str)
{
	char	c;

	c =  '0' + (num % 10);
	if (num < 10)
	{
		*str = c;
		// *(str + 1) = '\0';
		return ;
	}
	unsigned_to_str2(num / 10, str - 1);
	*str = c;
}

char	*unsigned_to_str(unsigned int num)
{
	char	*str;
	int		size;

	size = size_of_unsigned(num);
	str = malloc (size + 1);
	if (!str)
		exit (1);
	str[size] = '\0';
	unsigned_to_str2(num, str + size - 1);
	return (str);
}