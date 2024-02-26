/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:01:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/02/26 14:04:20 by ealislam         ###   ########.fr       */
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

# define H_DOC_PATH "./docs/"

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

//binary tree***********************************
typedef struct s_tree
{
	char			**cmd;
	e_oper			oper;
	struct s_tree	*left;
	struct s_tree	*right;
	int				input;
	int				output;
	int				here_doc;
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
}	t_all;


/*
 * Functions
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_write(char *str, int fd);
void    free_str(char *str);
void    free_arr(char **arr);
void    free_tree(t_tree *tree);
char	*unsigned_to_str(unsigned int num);


/*
 * Parse_env
*/
void	append_node(t_env **head, char *key, char *value);
t_env	*parse_env(char **env);

/*
 * Parse_tree
*/
int		parse_tree(char *str, t_all *tree, char **error);


#endif