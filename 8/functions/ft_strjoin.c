/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:58:41 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/29 14:54:09 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*ft_strjoin(char const *s1, char const *s2, char **error)
{
	char	*str;
	char	*result;		

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0, error);
	if (str == NULL)
		exit(1);
	result = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (result);
}
