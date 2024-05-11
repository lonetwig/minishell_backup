/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:51:24 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/11 13:20:29 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	pwd(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			printf("%s\n", tmp->value);
			exit_stat(0, 1);
			return (1);
		}
		tmp = tmp->next;
	}
	printf("%s\n", getcwd(NULL, 0));
	exit_stat(0, 1);
	return (1);
}
