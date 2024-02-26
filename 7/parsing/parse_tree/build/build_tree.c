/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 16:33:44 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_tree.h"

static t_tree	*add_branch(char **l_r, e_oper oper, int *doc_i, char **error)
{
	t_tree	*tree;
	char	**pre_env_arr;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (*error = "minibash: malloc failed", NULL);
	*tree = (t_tree){0};
	if (oper)
	{
		tree->oper = oper;
		tree->output = 1;
	}
	else
	{
		pre_env_arr = split_by_space(l_r[0]);
		get_environment(&(l_r[0]));
		tree->cmd = split_by_space(l_r[0]);
		tree->input = get_input_output(tree->cmd, 0, pre_env_arr);
		tree->output = get_input_output(tree->cmd, 1, pre_env_arr);
		tree->here_doc = get_here_doc(&tree->input, *doc_i);
		get_wildcard(tree->cmd);
		free_arr(pre_env_arr);
		(*doc_i)++;
	}
	return (tree);
}

static int	handle_parentheses(void **data, char **err, e_oper opr, int *doc_i)
{
	char	*str;
	t_tree	**tree;
	t_tree	**root;

	str = data[0];
	tree = data[1];
	root = data[2];
	*tree = add_branch(NULL, opr, doc_i, err);
	if (*err)
		return ;
	str = split_by_parantheses(str, &(*tree)->input, &(*tree)->output);
	(*tree)->here_doc = get_here_doc(&(*tree)->input, *doc_i);
	(*doc_i)++;
	build_tree(str, &(*tree)->left, root, err);
}

void    build_tree(char *str, t_tree **tree, t_tree **root, char **error)
{
	static int	doc_index;
	char		**left_right;
	e_oper		oper;
	
	oper = split_cmds_queue(str, &left_right);
	if (oper == PARENTHESES)
	{
		handle_parentheses((void **){str, tree, root}, error, oper, doc_index);
		// *tree = add_branch(NULL, oper, &doc_index, error);
		// str = split_by_parantheses(str, &(*tree)->input, &(*tree)->output);
		// (*tree)->here_doc = get_here_doc(&(*tree)->input, doc_index);
		// doc_index++;
		// build_tree(str, &(*tree)->left, root, error);
		return ;
	}
	*tree = add_branch(left_right, oper, &doc_index, error);
	if (!(*root) && !*error)
		*root = *tree;
	if (str && (*tree)->oper && !*error)
	{
		build_tree(left_right[0], &(*tree)->left, root, error);
		build_tree(left_right[1], &(*tree)->right, root, error);
	}
	doc_index = 0;
}
