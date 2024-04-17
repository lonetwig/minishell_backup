/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:51:24 by azainabi          #+#    #+#             */
/*   Updated: 2024/03/11 23:05:16 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) != NULL)
		printf("%s\n", buff);
	else
	{
		ft_write("minibash: ", 2, 0);
		perror("");
		exit_stat(1, 1);
		return (0);
	}
	exit_stat(0, 1);
	return (1);
}