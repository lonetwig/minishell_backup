/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 05:08:01 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/22 02:24:17 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minibash.h"

static void	free_key_val(t_env **env, char *arg)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, arg, (ft_strlen(tmp->key) + 1)))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			tmp->key = NULL;
			tmp->value = NULL;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(t_all *all, t_env *env, char **cmd)
{
	int		i;
	int		j;
	int		flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		get_environment(all, &(cmd[i]));
		j = 0;
		if (!cmd[i][j])
		{
			ft_write("unset: `", 2, 0);
			ft_write(cmd[i], 2, 0);
			ft_write("\" is not a valid identifier", 2, 1);
			exit_stat(1, 1);
			flag = 1;
		}
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) || !ft_isunder_alpha(cmd[i][j]))
			{
				ft_write("minibash: unset: `", 2, 0);
				ft_write(cmd[i], 2, 0);
				ft_write("\" is not a valid identifier", 2, 1);
				exit_stat(1, 1);
				flag = 1;
			}
			j++;
		}
		free_key_val(&env, cmd[i]);
		i++;
	}
	if (!flag)
		exit_stat(0, 1);
	return (1);
}