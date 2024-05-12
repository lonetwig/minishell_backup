/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:42:43 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/12 17:18:16 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// user made write function
void	ft_write(char *str, int fd, int new_line)
{
	while (*str)
	{
		write (fd, str, 1);
		str++;
	}
	if (new_line == 1)
		write(fd, "\n", 1);
}
