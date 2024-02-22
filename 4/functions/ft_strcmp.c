/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:20:58 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/22 14:01:34 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minibash.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*s_1;
	const unsigned char	*s_2;

	i = 0;
	s_1 = (const unsigned char *)s1;
	s_2 = (const unsigned char *)s2;
	while ((*s_1 || *s_2))
	{
		// printf ("%s %s\n", s1, s2);
		if (*s_1 != *s_2)
			return (*s_1 - *s_2);
		s_1++;
		s_2++;
		i++;
	}
	return (0);
}
