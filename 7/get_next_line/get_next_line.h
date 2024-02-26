/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:45:42 by ealislam          #+#    #+#             */
/*   Updated: 2023/11/27 08:59:33 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_size
{
	unsigned int	s_to_nl;
	unsigned int	s_to_null;
}	t_size;

char	*get_next_line(int fd);
t_size	get_s(char *str);
void	str_join(char *cur_bfr, char **fnl_str, char *new_dst);
int		check_n(char *cur_bfr);
char	*free_and_return_null(char **remain, char **final, char **cur_buf);
#endif