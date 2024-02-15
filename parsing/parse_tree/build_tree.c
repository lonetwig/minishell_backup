/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/15 12:18:04 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

void    build_tree(char *str, char direction)
{
	e_oper	oper_type;
	char	**left_right;
	
	printf("in %c : %s \n", direction, str);
	if (str && split_cmds_queue(str, &oper_type, &left_right))
	{
		build_tree(left_right[0], 'l');
		build_tree(left_right[1], 'r');
	}

}