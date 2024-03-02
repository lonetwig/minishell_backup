/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:22:23 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 09:29:50 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	free_all(t_malloc *all_alloc)
{
	while(all_alloc)
	{
		free(all_alloc);
		all_alloc = all_alloc->next;
	}
}

static int	add_node(t_malloc *all_alloc, void *ptr)
{
	while (all_alloc->next)
		all_alloc = all_alloc->next;
	all_alloc->next = malloc(sizeof(t_malloc));
	if (!all_alloc->next)
		return (1);
	all_alloc->next->ptr = ptr;
	all_alloc->next->next = NULL;
	return (0);
}

void	*ft_malloc(unsigned int size, int free, char **error)
{
	static t_malloc	all_alloc = {NULL, NULL};
	void			*ptr;

	ptr = NULL;
	if (free)
		free_all(all_alloc.next);
	else
	{
		ptr = malloc(size);
		if (!ptr || add_node(&all_alloc, ptr))
			return (*error = "Minibash: Malloc has failed", NULL);
	}
	return (ptr);
}
