/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:32:55 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 16:05:05 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H
#include "../../minibash.h"

typedef struct s_check_quote
{
	int	is_dq;
	int	is_sq;
}	t_check_quote;

typedef struct s_split
{
	char			*str;
	char			**arr;
	int				arr_len;
	int				c_p;
	t_check_quote	c_q;
}	t_split;

typedef struct s_paranth_quotes
{
	t_check_quote	c_q;
	int				i_p;
}	t_paranth_quotes;

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
}	t_str_list;

int		parse_tree(char *str, t_all *tree, char **error);
void    build_tree(char *str, t_tree **tree, t_tree **root, char **error);
void	check_quotes(char c, t_check_quote *c_q);
void	check_opers(char *str, char **error);
void	check_q_p(char *str, char **error);
void	check_parentheses(char c, int *i_p);
int		check_wildcard(char *file, char *patt);
void	check_here_doc(char *str, char **error);
int		cond_oper(char *str, e_oper oper);
int		cond_q(t_check_quote c_q);
int		cond_space(char *str, int i);
int		cond_jump_quote(char c, t_check_quote c_q);
int		cond_redirect(char *str);
void	get_environment(char **str);
void	get_files(t_str_list **all_files);
void	get_wildcard(char **arr);
int		get_input_output(char **arr, int expected, char **pre_env_arr);
int		get_here_doc(int *input_fd, int here_doc_i);
void    get_error(char *error, int fd, t_tree *tree);
e_oper	split_cmds_queue(char *s, char ***left_right);
char	**split_by_oper(char *str, e_oper oper_type, char c[2]);
char	**split_by_space(char *s);
int		split_by_space2(t_split *all);
char	*split_by_parantheses(char *str, int *input, int *ouput);
char	*adjust_redirectionals(char *str, char **error);

#endif