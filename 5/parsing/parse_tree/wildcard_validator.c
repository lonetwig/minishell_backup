/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:11:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/22 16:51:05 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static void	handle_star(char **file, char **patt)
{
	if (**patt == '*')
	{
		while (**patt && **patt == '*')
			(*patt)++;
		while (**file && **file != **patt)
			(*file)++;
	}
}

static int	validate(char *file, char *patt)
{
	char	*original_patt;
	original_patt = patt;

	if (*patt != '*' && *file != *patt)
		return (0);
	handle_star(&file, &patt);
	while (*patt && *patt == *file)
		(file++ && patt++);
	if (*file && *patt == '*')
		return (validate(file, patt));
	if (*file && *patt && *patt != *file)
		return (validate(file, original_patt));
	if (*patt == '*')
		return (validate(file, patt));
	if (!*patt && !*file)
		return (1);
	return (0);
}

int	wildcard_validator(char *file, char *patt)
{
	// printf("file %s patt %s\n", file, patt);
	if (*patt == '.' && *file != '.')
		return (0);
	else if (*patt != '.' && *file == '.')
		return (0);
	return (validate(file, patt));
}
