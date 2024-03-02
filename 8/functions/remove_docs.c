/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_docs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:33:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/27 11:22:00 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	remove_docs()
{
	t_str_list	*docs;
	// t_str_list	*head;
	char		*proc_name;

	get_files(&docs, H_DOC_PATH);
	// head = docs;
	while (docs)
	{
		proc_name = unsigned_to_str(getpid());
		if (ft_strncmp(docs->str, proc_name, ft_strlen(proc_name)))
		{
			unlink(ft_strjoin(H_DOC_PATH,ft_strjoin(docs->str, proc_name)));
			while (*(docs->str) && *(docs->str) == *proc_name)
				docs->str++;
			close(ft_atoi(docs->str));
		}
		docs = docs->next;
	}
}
