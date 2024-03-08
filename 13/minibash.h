/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:01:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/03/07 12:06:05 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBASH_H
# define MINIBASH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "get_next_line/get_next_line.h"


# define H_DOC_PATH "/tmp/"
// # define H_DOC_PATH "./test/"

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
	AND,
	PARENTHESES
}	e_oper;

typedef enum e_open_modes_
{
	OPEN_TRUNC,
	OPEN_APPEND,
	OPEN_READ
}	e_open_modes;

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

typedef struct s_all_fd
{
	int				fd;
	struct s_all_fd	*next;
}	t_all_fd;


//binary tree***********************************
typedef struct s_tree
{
	char			**cmd;
	char			*cmd_str;
	e_oper			oper;
	struct s_tree	*left;
	struct s_tree	*right;
	int				input;
	int				output;
	int				here_doc;
	int				doc_i;
	char			**env;
}	t_tree;


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

//-----------
// all in one struct
typedef struct s_all
{
	t_env	*env;
	t_tree	*tree;
	int		status;
}	t_all;


typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

typedef struct s_check_hdoc
{
	int					here_doc_i;
	int					p_tracker;
	int					i_p;
	t_check_quote		c_q;
}	t_check_hdoc;

/*
 * Functions
*/
char	*ft_substr(char const *s, unsigned int start, size_t len, char **err);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str, char **error);
char	*ft_strjoin(char const *s1, char const *s2, char **error);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_write(char *str, int fd);
char	*unsigned_to_str(unsigned int num, char **err);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_malloc(unsigned int size, int free, char **error);
void	remove_docs(char **err);
int		ft_open(char *path, e_open_modes mode, char **err, int close_mode);

/*
 * Parse tree
*/
int		parse_tree(char *str, t_all *tree, char **error);
void    build_tree(char *str, t_tree **tree_root[2], char **err, int *doc_i);
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
void	get_environment(char **str, char **err);
void	get_files(t_str_list **all_files, char *path, char **err);
void	get_wildcard(char **arr, char **err);
int		get_input_output(char **arr, int expected, char **pre_env, char **err);
int		get_here_doc(char *str, int *input_fd, int here_doc_i, char **err);
e_oper	split_cmds_queue(char *s, char ***left_right, char **err);
char	**split_by_oper(char *str, e_oper oper_type, char c[2], char **err);
char	**split_by_space(char *s, char **err);
int		split_by_space2(t_split *all, char **err);
char	*split_by_parantheses(char *str, int *input, int *ouput, char **err);
char	*adjust_redirectionals(char *str, char **error);
int		get_cmd_info(t_tree *branch, char **err);

/*
 * Parse_env
*/
void	append_node(t_env **head, char *key, char *value, char **err);
t_env	*parse_env(char **env);

/*
 * Parse_tree
*/
int		parse_tree(char *str, t_all *tree, char **error);


#endif