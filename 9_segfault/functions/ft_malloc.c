/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:22:23 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 16:03:44 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	free_all(t_malloc *all_alloc)
{
	t_malloc	*tmp;

	all_alloc = all_alloc->next;
	while (all_alloc)
	{
        free(all_alloc->ptr);
        tmp = all_alloc;
        all_alloc = all_alloc->next;
        free(tmp);
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
	static t_malloc	all_alloc = {"head", NULL};
	void			*ptr;

	ptr = NULL;
	if (free)
	{
		free_all(all_alloc.next);
		all_alloc.next = NULL;
		return (NULL);
	}
	if(!*error)
	{
		ptr = malloc(size);
		if (!ptr || add_node(&all_alloc, ptr))
			return (*error = "Minibash: Malloc has failed\n", NULL);
	}
	return (ptr);
}
