/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:20:39 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/05 15:32:40 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minibash.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*str;
	char	*error;
	t_all	all;

	error = NULL;
	while (1)
	{
		all.tree = NULL;
		if (!error)
			str = readline("minibash 🙌 >");
		else
		{
			ft_write(error, 2);
			str = readline("minibash 💀 >");
			error = NULL;
		}
		parse_tree(str, &all, &error);
		remove_docs(&error);
		ft_open(NULL, 0, NULL, 1);
		ft_malloc(0, 1, NULL);
		free (str);
	}
}
