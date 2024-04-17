/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:05:40 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/17 15:12:13 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	copy_key(char **env, t_var *var, t_all *all)
{
	var->tmp_key = ft_substr(env[var->i], 0, var->j, all);
	if (!var->tmp_key)
	{
		ft_write("Malloc error", 2, 1);
		exit(2);
	}
	var->rem = var->j + 1;
}

t_env	*parse_env(char **env, t_all *all)
{
	t_var	var;
	t_env	*head;

	head = NULL;
	var.i = 0;
	while (env[var.i])
	{
		var.j = 0;
		while (env[var.i][var.j] != '=')
			var.j++;
		if (env[var.i][var.j] == '=')
			copy_key(env, &var, all);
		var.j = 0;
		while (env[var.i][var.j])
			var.j++;
		var.tmp_val = ft_substr(env[var.i], var.rem, var.j - var.rem, all);
		if (!var.tmp_val)
		{
			ft_write("Malloc error", 2, 1);
			exit(2);
		}
		append_node(&head, var.tmp_key, var.tmp_val, all);
		var.i++;
	}
	return (head);
}
