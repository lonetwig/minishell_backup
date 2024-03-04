/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:05:40 by azainabi          #+#    #+#             */
/*   Updated: 2024/03/03 12:54:38 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	copy_key(char **env, t_var *var, char **err)
{
	var->tmp_key = ft_substr(env[var->i], 0, var->j, err);
	if (!var->tmp_key)
		error_exit("Error substr", 2);
	var->rem = var->j + 1;
}

t_env	*parse_env(char **env, char **err)
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
			copy_key(env, &var, err);
		var.j = 0;
		while (env[var.i][var.j])
			var.j++;
		var.tmp_val = ft_substr(env[var.i], var.rem, var.j - var.rem, err);
		if (!var.tmp_val)
			error_exit("Error substr", 2);
		append_node(&head, var.tmp_key, var.tmp_val, err);
		var.i++;
	}
	return (head);
}
