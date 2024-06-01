/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:19:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/28 19:49:01 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	ft_exit(char **cmd, t_all *all)
{
	int	exit_st;
	int	i;

	exit_st = exit_stat(0, 0);
	i = 0;
	while (cmd && cmd[i])
		i++;
	ft_write("exit", 1, 1);
	if (i > 2)
	{
		ft_write("minibash: exit: too many arguments", 2, 1);
		exit_st = 1;
		exit_stat(1, 1);
		return ;
	}
	if (cmd && cmd[1] && i <= 2)
		exit_st = ft_atoi(cmd[1]);
	remove_docs(all);
	ft_open(NULL, 0, NULL, 1);
	ft_malloc(0, 1, NULL);
	exit(exit_st);
}
