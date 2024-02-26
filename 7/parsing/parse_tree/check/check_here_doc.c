/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:05:54 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 15:34:21 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_tree.h"

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
		*error = "minibash: syntax error";
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

	delim = malloc(delimiter_size(s, error) + 2);
	if (!delim)
		return (*error = "minibash: malloc failed.\n", NULL);
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

static void	fill_doc(int doc_fd, char *delimiter)
{
	char	*str;
	int		i;

	if (!delimiter)
		return ;
	str = get_next_line(1);
	while (ft_strcmp(str, delimiter))
	{
		i = 0;
		while (str[i])
		{
			write(doc_fd, str + i, 1);
			i++;
		}
		free_str(str);
		str = NULL;
		str = get_next_line(1);
	}
	free_str(str);
	free_str(delimiter);
}

static int	create_doc(unsigned int here_doc_i, unsigned int pid, char *str, \
char **error)
{
	char	*str1;
	char	*str2;
	char	*doc_name;
	int		doc_fd;

	str1 = unsigned_to_str(pid);
	str2 = unsigned_to_str(here_doc_i);
	doc_name = ft_strjoin(str1, str2);
	str1 = doc_name;
	doc_name = ft_strjoin(H_DOC_PATH, doc_name);
	free_str(str1);
	doc_fd = open(doc_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (doc_fd < 0)
		return (close(doc_fd), *error = "minibash: open failed.\n", 1);
	fill_doc(doc_fd, get_delimiter(str, error));
	free_str(str2);
	free_str(doc_name);
	close(doc_fd);
	return (0);
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
			create_doc(here_doc_i, getpid(), str + 2, error);
		if (*error)
			return ;
		str++;
	}
}
