/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/23 17:27:00 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static t_tree	*add_branch(char **left_right, e_oper oper, int *here_doc_i)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		exit(1);
	*tree = (t_tree){0};
	if (oper)
	{
		tree->oper = oper;
		tree->output = 1;
	}
	else
	{
		append_env(&(left_right[0]));
		tree->cmd = split_by_space(left_right[0]);
		tree->input = get_input_output(tree->cmd, 0);
		tree->output = get_input_output(tree->cmd, 1);
		tree->here_doc = get_here_doc(&tree->input, *here_doc_i);
		wildcard(tree->cmd);
		(*here_doc_i)++;
	}
	return (tree);
}

void    build_tree(char *str, t_tree **tree, t_tree **root)
{
	static int	here_doc_index;
	char		**left_right;
	e_oper		oper;
	
	oper = split_cmds_queue(str, &left_right);
	if (oper == PARENTHESES)
	{
		*tree = add_branch(NULL, oper, &here_doc_index);
		(*tree)->input = 0;
		build_tree(split_by_parantheses(str), &((*tree)->left), root);
		return ;
	}
	*tree = add_branch(left_right, oper, &here_doc_index);
	if (!(*root))
		*root = *tree;
	if (str && (*tree)->oper)
	{
		build_tree(left_right[0], &((*tree)->left), root);
		build_tree(left_right[1], &((*tree)->right), root);
	}
	here_doc_index = 0;
}
