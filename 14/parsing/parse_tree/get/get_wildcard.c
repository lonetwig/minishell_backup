/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:53:51 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 09:03:14 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

void	append_filename(char *filename, char **new_str, char **err)
{
	char	*tmp;

	tmp = *new_str;
	if (!*new_str)
		*new_str = ft_strdup(filename, err);
	else
		*new_str = ft_strjoin(*new_str, filename, err);
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, " ", err);
}

int	wildcard_exist(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

void	find_wildcard(char **arr, t_str_list *files, char **err)
{
	t_str_list	*tmp_files;
	char		*new_str;

	tmp_files = files;
	new_str = NULL;
	while (*arr)
	{
		if (!wildcard_exist(*arr) && arr++)
			continue ;
		while (files)
		{
			if (check_wildcard(files->str, *arr))
				append_filename(files->str, &new_str, err);
			files = files->next;
		}
		if (new_str)
			*arr = new_str;
		new_str = NULL;
		files = tmp_files;
		arr++;
	}
}

void	get_wildcard(char **arr, char **err)
{
	t_str_list	*all_files;

	all_files = NULL;
	get_files(&all_files, ".", err);
	find_wildcard(arr, all_files, err);
}
