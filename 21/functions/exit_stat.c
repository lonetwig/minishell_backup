/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:37:03 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/12 17:23:37 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// used to assign the exit code, it uses a static variable
// returns the current exit code
// in case of passing flag 1, the exit code changes to the code passed
int	exit_stat(int code, int flag)
{
	static int	exit_code = 0;

	if (flag == 1)
		exit_code = code;
	return (exit_code);
}
