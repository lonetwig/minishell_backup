/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/02 17:50:19 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

static t_tree	*add_branch(char **l_r, e_oper oper, int *doc_i, char **error)
{
	t_tree	*tree;
	char	**pre_env_arr;

	tree = ft_malloc(sizeof(t_tree), 0, error);
	if (!tree)
		return (NULL);
	*tree = (t_tree){0};
	if (oper)
	{
		tree->oper = oper;
		tree->output = 1;
	}
	else
	{
		pre_env_arr = split_by_space(l_r[0], error);
		get_environment(&(l_r[0]), error);
		tree->cmd = split_by_space(l_r[0], error);
		tree->input = get_input_output(tree->cmd, 0, pre_env_arr, error);
		tree->output = get_input_output(tree->cmd, 1, pre_env_arr, error);
		tree->here_doc = get_here_doc(&tree->input, *doc_i, error);
		printf("%d %d %d\n",tree->input, tree->output,tree->here_doc);
		get_wildcard(tree->cmd, error);
		(*doc_i)++;
	}
	return (tree);
}

static void	handle_parentheses(void **data, char **err, e_oper opr, int *doc_i)
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
	str = split_by_parantheses(str, &(*tree)->input, &(*tree)->output, err);
	if (*err)
		return ;
	(*tree)->here_doc = get_here_doc(&(*tree)->input, *doc_i, err);
	(*doc_i)++;
	if (!str)
		return ;
	build_tree(str, &(*tree)->left, root, err);
}

void    build_tree(char *str, t_tree **tree, t_tree **root, char **error)
{
	static int	doc_index;
	char		**left_right;
	e_oper		oper;
	
	if (!str)
		return ;
	oper = split_cmds_queue(str, &left_right, error);
	printf("0000\n");
	if (oper == PARENTHESES)
	{
		handle_parentheses((void *[3]){str, tree, root}, error, oper, &doc_index);
		return ;
	}
	*tree = add_branch(left_right, oper, &doc_index, error);
	if (!(*root) && !*error)
		*root = *tree;
	printf("(%s %s)\n", left_right[0], left_right[1]);
	printf("111\n");
	if (str && (*tree)->oper && !*error)
	{
		printf("222\n");
		build_tree(left_right[0], &(*tree)->left, root, error);
		build_tree(left_right[1], &(*tree)->right, root, error);
	}
	printf("3333\n");
	doc_index = 0;
}
