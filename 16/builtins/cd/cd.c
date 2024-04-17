/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:45:42 by azainabi          #+#    #+#             */
/*   Updated: 2024/03/10 02:12:32 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

int	cd(char **arg, t_all *all)
{
	int	i;

	i = 1;
	if (!arg[i])
	{
		if (!check_key(all->env, "HOME"))
		{
			(all->error = "minibash: cd: HOME not set", exit_stat(1, 1));
			return (0);
		}
		else
		{
			if (chdir(get_value(all->env, "HOME")) == -1)
			{
				(all->error = strerror(errno), exit_stat(1, 1));
				return (0);
			}
		}
	}
	else
	{
		if (arg[1][ft_strlen(arg[1]) - 1] == '\\' && arg[2])
		{
			arg[1] = ft_strjoin(ft_substr(arg[1], 0, ft_strlen(arg[1]) - 1, all), " ", all);
			arg[1] = ft_strjoin(arg[1], arg[2], all);
		}
		if (chdir(arg[1]) == -1)
		{
			(all->error = strerror(errno), exit_stat(1, 1));
			return (0);
		}
	}
	exit_stat(0, 1);
	return (1);
}
