/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 07:02:05 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/17 15:26:03 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*ft_strdup(const char *str, t_all *all, \
void *(*ft_malloc)(unsigned int s, int f, t_all *a))
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	ptr = ft_malloc(sizeof(char) * (len + 1), 0, all);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
