/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_docs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:33:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 16:06:42 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	remove_docs(char **err)
{
	t_str_list	*docs;
	char		*path;
	char		*pid;

	get_files(&docs, H_DOC_PATH, err);
	while (docs)
	{
		pid = unsigned_to_str(getpid(), err);
		path = ft_strjoin(H_DOC_PATH, pid, err);
		if (!ft_strncmp(docs->str, pid, ft_strlen(pid)))
		{
			path = ft_strjoin(H_DOC_PATH, docs->str, err);
			unlink(path);
		}
		docs = docs->next;
	}
}
