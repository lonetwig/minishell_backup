/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:19:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 09:49:48 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_tree.h"

int	get_here_doc(int *input_fd, int here_doc_i)
{
	char	*str1;
	char	*str2;
	char	*doc_name;
	int		doc_fd;

	str1 = unsigned_to_str(getpid());
	str2 = unsigned_to_str(here_doc_i);
	doc_name = ft_strjoin(str1, str2);
	if (access(doc_name, F_OK) == -1)
		return (0);
	doc_fd = open(doc_name, O_RDONLY, 0777);
	if (doc_fd < 0)
		exit(1);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (doc_name)
		free(doc_name);
	close(*input_fd);
	*input_fd = 0;
	return (doc_fd);
}
