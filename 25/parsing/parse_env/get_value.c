/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:19:57 by azainabi          #+#    #+#             */
/*   Updated: 2024/06/03 15:04:16 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

char	*get_value(t_env *env, char *key, t_all *all)
{
	t_env	*tmp;

	if (!env || !key)
		return (NULL);
	if (key[0] == '\\')
	{
		printf("key : %s\n", key);
		all->t_val = key;
		all->t_val2 = ft_strjoin("'", all->t_val + 1, all);
		key = ft_strjoin(all->t_val2, "'", all);
		return (key);
	}
	tmp = env;
	while (tmp)
	{
		if (!tmp->key)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
