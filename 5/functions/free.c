/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:10 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/23 14:14:57 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minibash.h"

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
