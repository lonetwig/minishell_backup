/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:07:21 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/16 13:52:51 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static t_tree	*add_branch(char *str, char **left_right, e_oper oper)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		exit(1);
	if (oper)
	{
		tree->cmd = NULL;
		tree->oper = oper;
	}
	else
	{
		append_env(&(left_right[0]));
		tree->cmd = split_by_space(left_right[0]);
		tree->oper = NONE;
	}
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

void    build_tree(char *str, t_tree **tree, t_tree **root)
{
	
	char	**left_right;
	e_oper	oper;

	oper = split_cmds_queue(str, &left_right);
	*tree = add_branch(str, left_right, oper);
	if (!(*root))
		*root = *tree;
	if (str && (*tree)->oper)
	{
		build_tree(left_right[0], &((*tree)->left), root);
		build_tree(left_right[1], &((*tree)->right), root);
	}
}
