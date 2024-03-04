/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:19:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/04 13:20:55 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

int	get_here_doc(int *input_fd, int here_doc_i, char **err)
{
	char	*str1;
	char	*str2;
	char	*doc_name;
	int		doc_fd;

	str1 = unsigned_to_str(getpid(), err);
	str2 = unsigned_to_str(here_doc_i, err);
	doc_name = ft_strjoin(str1, str2, err);
	if (access(doc_name, F_OK) == -1)
		return (0);
	doc_fd = ft_open(doc_name, OPEN_READ, err, 0);
	if (doc_fd < 0)
		return (-1);
	ft_open(NULL, 0, NULL, *input_fd);
	*input_fd = 0;
	return (doc_fd);
}
