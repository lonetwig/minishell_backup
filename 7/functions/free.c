/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:10 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 12:48:33 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void    free_str(char *str)
{
    if (str)
        free(str);
}

void    free_arr(char **arr)
{
    char    **tmp;

    tmp = arr;
    while (arr && *arr)
    {
        free(*arr);
        arr++;
    }
    if (tmp)
        free(tmp);
}

void    free_tree(t_tree *tree)
{
    
}
