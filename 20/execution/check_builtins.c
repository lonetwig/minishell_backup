/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:44:54 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/11 12:19:50 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	check_builtins(t_tree *node, t_all *all)
{
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (echo(all, node->cmd), 1);
	else if (!ft_strcmp(ft_tolower(node->cmd[0]), "export"))
		return (export(all, all->env, node->cmd), 1);
	else if (!ft_strcmp(ft_tolower(node->cmd[0]), "unset"))
		return (unset(all, all->env, node->cmd), 1);
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		return (pwd(all), 1);
	else if (!ft_strcmp(ft_tolower(node->cmd[0]), "cd"))
		return (cd(node->cmd, all), 1);
	else if (!ft_strcmp(ft_tolower(node->cmd[0]), "env"))
		return (env(all->env), 1);
	else if (!ft_strcmp(ft_tolower(node->cmd[0]), "exit"))
		return (ft_exit(all), 1);
	return (0);
}
