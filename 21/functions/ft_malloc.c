/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:22:23 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/12 12:46:45 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// used to free all the allocations in the list
static void	free_all(t_malloc *all_alloc)
{
	t_malloc	*tmp;

	while (all_alloc)
	{
		if (all_alloc->ptr != NULL)
			free(all_alloc->ptr);
		tmp = all_alloc;
		all_alloc = all_alloc->next;
		free(tmp);
	}
}

// used to add a node to the list
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

// this is a user made malloc function.
// it uses a static variable (list) to keep track of all alocated data
// in case of passing > 0 to free, the function free all the allocated data 
void	*ft_malloc(unsigned int size, int free, t_all *all)
{
	static t_malloc	all_alloc = {"head", NULL};
	void			*ptr;

	ptr = NULL;
	if (free)
	{
		free_all(all_alloc.next);
		all_alloc.next = NULL;
		return (NULL);
	}
	if (!all->error)
	{
		ptr = malloc(size);
		if (!ptr || add_node(&all_alloc, ptr))
			return (all->error = "Minibash: Malloc has failed\n", NULL);
	}
	return (ptr);
}
