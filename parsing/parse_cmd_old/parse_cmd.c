/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:32:45 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/13 13:34:36 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

void	parse_cmd(char *str)
{
	char	**all_cmds_arr;
	t_oper	*all_opers_arr;
	char	*cmds_list;

	all_cmds_arr = split_by_oper(str);
    append_env(all_cmds_arr);
    get_cmds_list(all_cmds_arr, &cmds_list);
    while (*all_cmds_arr)
	{
		printf("%s\n\n", *all_cmds_arr);
		all_cmds_arr++;
	}
	
	// all_opers = get_opers;
}

// dont forget:
// change the $ only if it isnt $? xxx
// check the / for the spaces 
// check the space in the quotes
// check the 

int main()
{	
    parse_cmd("echo \"aaa $q");

}