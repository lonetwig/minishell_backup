/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/26 16:22:22 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_tree.h"

void printTree(t_tree *root, int i, char *str) {
	if (root != NULL) 
	{
		if (root->oper)
			printf("in %d %s operator %d:(out %d in %d h_doc %d)\n\n",i ,str, root->oper, root->output, root->input, root->here_doc);
		if (root->cmd)
		{
			printf("in %d %s :(out %d in %d h_doc %d)\n",i, str, root->output, root->input, root->here_doc);
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
//***************************************************
int    parse_tree(char *str, t_all *all, char **error)
{
	t_tree  *root;

	root = NULL;
	if ((check_here_doc(str, error), *error) || \
		(check_q_p(str, error), *error) || \
		(check_opers(str, error), *error) || \
		(str = adjust_redirectionals(str, error), *error) || \
		(build_tree(str, &all->tree, &root, error), *error))
		return (all->tree = root, 1);
	all->tree = root;
	printTree(root, 0, "start");
	return (0);
}
