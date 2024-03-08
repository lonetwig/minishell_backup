/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:26:55 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 10:01:19 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	close_fd(t_all_fd *all_fd, int fd)
{
	while (all_fd)
	{
		if (all_fd->fd == fd)
		{
			close(all_fd->fd);
			all_fd->fd = -1;
			return ;
		}
		all_fd = all_fd->next;
	}
}

static void	close_all_fd(t_all_fd *all_fd)
{
	all_fd = all_fd->next;
	while (all_fd)
	{
		if (all_fd->fd > 1)
			close(all_fd->fd);
		all_fd = all_fd->next;		
	}
}

static int	append_fd(t_all_fd *all_fd, int fd, char **err)
{
	t_all_fd	*node;

	node = ft_malloc(sizeof(t_all_fd), 0, err);
	if (!node)
		return (1);
	node->fd = fd;
	node->next = NULL;
	while (all_fd->next)
		all_fd = all_fd->next;
	all_fd->next = node;
	return (0);
}


int	ft_open(char *path, e_open_modes mode, char **err, int close_mode)
{
	static t_all_fd	all_fd = {-1, NULL};
	int	fd;
	int	flags;

	if (close_mode > 1)
		return (close_fd(&all_fd, close_mode), -1);
	if (close_mode == 1)
		return (close_all_fd(&all_fd), all_fd.next = NULL, 0);
	if (mode == OPEN_TRUNC)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (mode == OPEN_APPEND)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (mode == OPEN_READ)
		flags = O_RDONLY;
	fd = open(path, flags, 0777);
	if (fd < 0 || append_fd(&all_fd, fd, err))
		*err = "Minibash: Open has failed\n"; 
	return (fd);
}
