/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:23:27 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/17 09:30:36 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static t_str_list	*append_file(char *str, t_str_list *all_files)
{
	t_str_list	*file;

	file = malloc(sizeof(t_str_list));
	if (!file)
		exit(1);
	file->str = ft_strdup(str);
	file->next = NULL;
	if (!all_files)
		all_files = file;
	else
		all_files->next = file;
	return (file);
}

static int	same_dir_cond(char *str)
{
	if ((str[0] == '.' && str[1] == '\0') || \
	(str[0] == '.' && str[1] == '.' && str[2] == '\0'))
		return (1);
	return (0);
}

void	get_files(t_str_list **all_files)
{
	t_str_list		*tmp;
	t_str_list		*head;
	DIR				*dir;
	struct dirent	*entry;

	head = NULL;
	tmp = NULL;
	dir = opendir(".");
	if (!dir)
		exit(1);
	entry = readdir(dir);
	while (entry)
	{
		if (same_dir_cond(entry->d_name))
		{
			entry = readdir(dir);
			continue ;
		}
		tmp = append_file(entry->d_name, tmp);
		if (!head)
			head = tmp;
		entry = readdir(dir);
	}
	closedir(dir);
	*all_files = head;
}
