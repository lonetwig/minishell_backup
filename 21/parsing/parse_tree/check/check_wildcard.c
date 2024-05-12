/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:11:13 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/12 18:04:37 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

// jumps all the "*" in the pattern, and adjust the file name with the pattern
static void	handle_star(char **file, char **pattern)
{
	if (**pattern == '*')
	{
		while (**pattern && **pattern == '*')
			(*pattern)++;
		while (**file && **file != **pattern)
			(*file)++;
	}
}

//used to check if the filename is compatible with the pattern of the wildcard
static int	validate_wildcard(char *file, char *pattern)
{
	char	*original_pattern;

	original_pattern = pattern;
	if (*pattern != '*' && *file != *pattern)
		return (0);
	handle_star(&file, &pattern);
	while (*pattern && *pattern == *file)
	{
		file++;
		pattern++;
	}
	if (*file && *pattern == '*')
		return (validate_wildcard(file, pattern));
	if (*file && *pattern && *pattern != *file)
		return (validate_wildcard(file, original_pattern));
	if (*pattern == '*')
		return (validate_wildcard(file, pattern));
	if (!*pattern && !*file)
		return (1);
	return (0);
}

// compare if the given file name is compatible to the pattern of the wildcard
// then returns either 1 if it corresponds or 0 if not
int	check_wildcard(char *file, char *pattern)
{
	if (*pattern == '.' && *file != '.')
		return (0);
	else if (*pattern != '.' && *file == '.')
		return (0);
	return (validate_wildcard(file, pattern));
}
