/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:20:39 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/27 11:22:07 by ealislam         ###   ########.fr       */
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
		// get_error();
		if (!error)
			str = readline("minibash 🙌 >");
		else
		{
			// get_error();
			str = readline("minibash 💀 >");
			error = NULL;
		}
		if ((parse_tree(str, &all, &error), error))
			continue ;
	}
}