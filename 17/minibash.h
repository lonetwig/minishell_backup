/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:01:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/20 07:41:06 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBASH_H
# define MINIBASH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

// # include "get_next_line/get_next_line.h"


# define H_DOC_PATH "/tmp/"
// # define H_DOC_PATH "./test/"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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
}	t_e_oper;

typedef enum e_open_modes_
{
	OPEN_TRUNC,
	OPEN_APPEND,
	OPEN_READ
}	t_e_open_modes;

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
	t_e_oper			oper;
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
	char	*str;
}				t_var;

//-----------
// all in one struct
typedef struct s_all
{
	t_env	*env;
	t_tree	*tree;
	int		status;
	int		append;
	int		original_in;
	int		original_out;
	char	*error;
	char	*tmp;
	char	*tmp_val;
	char	**envp;
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

typedef struct s_size
{
	unsigned int	s_to_nl;
	unsigned int	s_to_null;
}	t_size;

/*
 * Get_next_line
*/

char	*get_next_line(int fd, char **remain, t_all *all);
t_size	get_s(char *str);
void	str_join(char *cur_bfr, char **fnl_str, char *new_dst);
int		check_n(char *cur_bfr);
char	*free_and_return_null(char **remain, char **final, char **cur_buf);

/*
 * Functions
*/
char	*ft_substr(char const *s, unsigned int start, size_t len, t_all *all);
char	**ft_split(char const *s, char c, t_all *all);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str, t_all *all);
char	*ft_strjoin(char const *s1, char const *s2, t_all *all);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_write(char *str, int fd, int new_line);
char	*unsigned_to_str(unsigned int num, t_all *all);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_malloc(unsigned int size, int free, t_all *all);
void	remove_docs(t_all *all);
int		ft_open(char *path, t_e_open_modes mode, t_all *all, int close_mode);
int		exit_stat(int code, int flag);
char	*ft_itoa(int n, t_all *all);
int		ft_isunder_alpha(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_tolower(char *c);

/*
 * Parse tree
*/
int		parse_tree(char *str, t_all *all);
void    build_tree(char *str, t_tree **tree_root[2], t_all *all, int *doc_i);
void	check_quotes(char c, t_check_quote *c_q);
void	check_opers(char *str, t_all *all);
void	check_q_p(char *str, t_all *all);
void	check_parentheses(char c, int *i_p);
int		check_wildcard(char *file, char *patt);
void	check_here_doc(char *str, t_all *all);
int		cond_oper(char *str, t_e_oper oper);
int		cond_q(t_check_quote c_q);
int		cond_space(char *str, int i);
int		cond_jump_quote(char c, t_check_quote c_q);
int		cond_redirect(char *str);
void	get_environment(t_all *all, char **s);
void	get_files(t_str_list **all_files, char *path, t_all *all);
char	**get_wildcard(char **arr, t_all *all);
int		get_input_output(char **arr, int expected, char **pre_env, t_all *all);
int		get_here_doc(char *str, int *input_fd, int here_doc_i, t_all *all);
t_e_oper	split_cmds_queue(char *s, char ***left_right, t_all *all);
char	**split_by_oper(char *str, t_e_oper oper_type, char c[2], t_all *all);
char	**split_by_space(char *s, t_all *all);
int		split_by_space2(t_split *all_s, t_all *all);
char	*split_by_parantheses(char *str, int *input, int *ouput, t_all *all);
char	*adjust_redirectionals(char *str, t_all *all);
int		get_cmd_info(t_tree *branch, t_all *all);
int		arr_size(char **arr);
void    fill_arr_with_str(char **arr, char *str, t_all *all);
void	arr_dup(char **src, char **dst, int max_size);
/*
 * Parse_env
*/
void	append_node(t_env **head, char *key, char *value, t_all *all);
t_env	*parse_env(char **env, t_all *all);
char	*get_value(t_env *env, char *key);

/*
 * Parse_tree
*/
int		parse_tree(char *str, t_all *tree);

/*
 * BUILTINS
*/

void	change_val(t_env **env, char **key_val, int append, t_all *all);
int		check_key(t_env *env, char *key);
void	export(t_all *all, t_env *env, char **arg);
void	print_export(t_env *env);
void	env(t_env *env);
int		pwd(t_all *all);
int		unset(t_all *all, t_env *env, char **cmd);
int		echo(t_all *all, char **arg);
int		cd(char **arg, t_all *all);
void	ft_exit(t_all *all);

/*
 * Execution
*/
char	*get_cmd_path(t_all *all, char *cmd);
int		execute(t_tree	*root, char **envp, t_all *all);
int		operator_exec(t_all *all);
void	execute_single_command(t_tree *node, char **envp, t_all *all);
void	is_a_dir(char *path, int *perm);
char	**linked_list_to_arr(t_all *all);
void	execute_command(t_tree *node, char **envp, t_all *all);
int		check_builtins(t_tree *node, t_all *all);

#endif