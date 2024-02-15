/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/15 12:20:38 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

void    parse_tree(char *str)
{
    t_tree  *tree;

    check_q_p(str);
    check_opers(str);
    printf("yyy\n");


    // find the most precedent opper, then split the string with it.
    // always put the left of command in left and the right of it in right
    // then repeat the same process on each side, untill no oper is left


    build_tree(str, 's');
    // append_env()


    printf("%s\n",str);


}

int main()
{
    parse_tree("hi this is | a test < file && echo hello && test | end  ");
}