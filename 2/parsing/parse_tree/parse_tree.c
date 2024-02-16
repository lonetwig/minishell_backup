/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/16 13:52:22 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

void printTree(t_tree *root, int i, char *str) {
	if (root != NULL) 
	{
		if (root->oper)
			printf("in %d %s : %d operator\n",i ,str, root->oper);
		if (root->cmd)
		{
			printf("in %d %s :\n",i, str);
			while(*(root->cmd))
				{
					printf("%s \n",*(root->cmd));
					(root->cmd)++;
				}
			printf("\n");
		}
		printTree(root->left, i + 1, "left");
		printTree(root->right, i + 1, "right");
	}
}

void    parse_tree(char *str)
{
	t_tree  *tree;
	t_tree  *root;

	root = NULL;
	check_q_p(str);
	check_opers(str);
	build_tree(str, &tree, &root);
	printTree(root, 0, "start");
}



int main()
{
	// parse_tree(" hi' this ''is | a test' | (< file && echo hello && test | ) && test' 'end  ");
	parse_tree("echo hello world && cat test 1 | tr ' ' \"x\" && print 5' 10' $ttt hi' this is | a test' && 'end' ");
}