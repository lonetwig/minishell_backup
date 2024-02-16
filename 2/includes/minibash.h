/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:01:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/16 11:37:47 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBASH_H
# define MINIBASH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

//Operators---------------------
typedef enum e_oper_
{
	NONE,
	PIPE,
	INPUT,
	H_DOC,
	OUTPUT,
	APPEND,
	OR,
	AND
}	e_oper;


//binary tree***********************************
typedef struct s_tree
{
	char			**cmd;
	e_oper			oper;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// typedef struct s_oper
// {
// 	t_special_char	oper;
// 	struct s_oper	*next;
// }	t_oper;

//commands------------------------
// typedef struct s_cmd
// {
// 	char			**cmd_arr;
// 	t_special_char	pre_oper;
// 	t_special_char	next_oper;
// 	struct s_cmd	*next;
// 	struct s_cmd	*pre;
// }	t_cmd;

//split function struct...........
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

//envirement----------------------
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_var
{
	int		i;
	int		j;
	int		rem;
	char	*tmp_key;
	char	*tmp_val;
}				t_var;

// all in one struct
typedef struct s_all
{
	t_env	*env;
}	t_all;


/*
 * Functions
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);

/*
 * Error
*/
void	error_exit(char *str, int x);

/*
 * Parse_env
*/
void	append_node(t_env **head, char *key, char *value);
t_env	*parse_env(char **env);

/*
 * parse_cmd
*/
// void	check_quotes(char c, t_check_quote *c_q);

/*
 * parse_tree
*/
void	check_quotes(char c, t_check_quote *c_q);
void	check_opers(char *str);
void	append_env(char **str);
void	check_q_p(char *str);
void	check_parentheses(char c, int *i_p);
char	**split_by_oper(char *str, e_oper oper_type, char c[2]);
void    build_tree(char *str, t_tree **tree, t_tree **root);
e_oper	split_cmds_queue(char *s, char ***left_right);
int		cond_oper(char *str, e_oper oper);
int		cond_q(t_check_quote c_q);
int		cond_space(char *str, int i);
int		cond_jump_quote(char c, t_check_quote c_q);
char	**split_by_space(char *s);
int		fill_arr(t_split *all);


// /*
//  * split_by_oper
// */
// int		check_delim(char c);
// char	**split_by_oper(char *s);
// int		fill_arr(t_split *all);


#endif