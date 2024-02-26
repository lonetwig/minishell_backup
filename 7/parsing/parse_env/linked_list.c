/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:22:28 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/26 12:48:55 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

t_env	*create_node(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		error_exit("Malloc failed at create_node", 1);
	env->key = ft_strdup(key);
	if (!env->key)
		error_exit("Malloc failed at create_node", 1);
	env->value = ft_strdup(value);
	if (!env->value)
		error_exit("Malloc failed at create_node", 1);
	env->next = NULL;
	return (env);
}

void	append_node(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = create_node(key, value);
	if (!head || !(*head))
	{
		(*head) = new_node;
		return ;
	}
	last_node = (*head);
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	last_node->next = new_node;
}
