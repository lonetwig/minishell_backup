/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:53:51 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/22 16:58:05 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

void	append_filename(char *filename, char **new_str)
{
	char	*tmp;

	tmp = *new_str;
	if (!*new_str)
		*new_str = ft_strdup(filename);
	else
		*new_str = ft_strjoin(*new_str, filename);
	if (tmp)
		free(tmp);
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, " ");
	if (tmp)
		free(tmp);
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

void	check_wildcard(char **arr, t_str_list *files)
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
			if (wildcard_validator(files->str, *arr))
				append_filename(files->str, &new_str);
			files = files->next;
		}
		if (new_str)
		{
			free(*arr);
			*arr = new_str;
		}
		new_str = NULL;
		files = tmp_files;
		arr++;
	}
}

void	wildcard(char **arr)
{
	t_str_list	*all_files;

	all_files = NULL;
	get_files(&all_files);
	check_wildcard(arr, all_files);
}
