/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:19:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/17 15:06:54 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

void	ft_exit(t_all *all)
{
	remove_docs(all);
	ft_open(NULL, 0, NULL, 1);
	ft_malloc(0, 1, NULL);
	ft_malloc_permanent(0, 1, NULL);
	printf("exit\n");
	exit(0);
}
