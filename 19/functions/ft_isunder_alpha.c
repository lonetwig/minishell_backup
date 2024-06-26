/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isunder_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 03:32:09 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/23 03:56:44 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	ft_isunder_alpha(int c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
