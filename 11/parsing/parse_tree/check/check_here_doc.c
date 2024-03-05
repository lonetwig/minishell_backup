/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:05:54 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/05 15:48:48 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static int	delimiter_size(char *s, char **error)
{
	char			*delim;
	t_check_quote	cq;
	int				i;
	int				count;

	i = 0;
	count = 0;
	cq = (t_check_quote){0};
	while (s[i] == ' ')
		i++;
	if (!s[i] || s[i] == '(' || s[i] == ')' || cond_oper(s + i, NONE))
		*error = "minibash: syntax error\n";
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && i++)
			continue;
		if (!cond_q(cq) && (s[i] == '(' || s[i] == ')' || \
		cond_oper(s + i, NONE) || s[i] == ' '))
			break ;
		i++;
		count++;
	}
	return (count);
}

static char	*get_delimiter(char *s, char **error)
{
	char			*delim;
	t_check_quote	cq;
	int				i;

	delim = ft_malloc(delimiter_size(s, error) + 2, 0, error);
	if (!delim)
		return (NULL);
	i = 0;
	cq = (t_check_quote){0};
	while (*s == ' ')
		s++;
	while (s[i])
	{
		check_quotes(s[i], &cq);
		if (((!cq.is_dq && s[i] == '\'') || (!cq.is_sq && s[i] == '"')) && s++)
			continue;
		if (!cond_q(cq) && (s[i] == '(' || s[i] == ')' || \
		cond_oper(s + i, NONE) || s[i] == ' '))
			break ;
		delim[i] = s[i];
		i++;
	}
	delim[i] = '\n';
	delim[i + 1] = '\0';
	return (delim);
}

static void	fill_doc(int doc_fd, char *delimiter, char **error)
{
	char	*str;
	int		i;
	char	*remain;

	if (!delimiter)
		return ;
	write(1, ">", 1);
	remain = NULL;
	str = get_next_line(0, &remain, error);
	while (ft_strcmp(str, delimiter))
	{
		i = 0;
		write(1, ">", 1);
		while (str[i])
		{
			write(doc_fd, str + i, 1);
			i++;
		}
		remain = NULL;
		str = get_next_line(0, &remain, error);
	}
}

static void	create_doc(unsigned int here_doc_i, char *str, \
char **error)
{
	char	*pid;
	char	*doc_i;
	char	*doc_name;
	int		doc_fd;

	pid = unsigned_to_str(getpid(), error);
	doc_i = unsigned_to_str(here_doc_i, error);
	doc_name = ft_strjoin(pid, doc_i, error);
	doc_name = ft_strjoin(H_DOC_PATH, doc_name, error);
	doc_fd = ft_open(doc_name, OPEN_TRUNC, error, 0);
	if (doc_fd < 0)
		return ;
	fill_doc(doc_fd, get_delimiter(str, error), error);
	ft_open(NULL, 0, NULL, doc_fd);
}

void	check_here_doc(char *str, char **error)
{
	int					here_doc_i;
	int					p_tracker;
	t_paranth_quotes	pq;

	here_doc_i = 0;
	p_tracker = 0;
	pq = (t_paranth_quotes){0};
	while (*str)
	{
		check_quotes(*str, &pq.c_q);
		check_parentheses(*str, &pq.i_p);
		if (!pq.i_p && p_tracker)
			here_doc_i++;
		p_tracker = pq.i_p;
		if (*str == ')')
			here_doc_i--;
		if (cond_oper(str, AND) || cond_oper(str, OR) || cond_oper(str, PIPE)\
		 || *str == '(')
			here_doc_i++;
		if (cond_oper(str, H_DOC))
			create_doc(here_doc_i, str + 2, error);
		if (*error)
			return ;
		str++;
	}
}
