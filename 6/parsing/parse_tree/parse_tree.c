/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/24 14:47:48 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

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

void    parse_tree(char *str)
{
	t_tree  *tree;
	t_tree  *root;

	root = NULL;
	check_here_doc(str);
	check_q_p(str);
	check_opers(str);
	str = adjust_redirectionals(str);
	build_tree(str, &tree, &root);
	printTree(root, 0, "start");
}



int main()
{
	// parse_tree(" hi' this ''is | a test' | (< file && echo hello && test | ) && test' 'end  ");
	// parse_tree("echo hello world && cat test 1 | tr ' ' \"x\" && print 5' 10' $ttt hi' this is | a test' && 'end' ");
	// parse_tree("echo c*o*.c *o.p.c | 2 ***o*c*.c ****** c*******o*.c c*****. && 3 c*.o c***on.c > 4 ****a.out** *.*****t $test || 5 '$' | 6 '$wc' $wc && 7 end > 8 bye");
	parse_tree("echo 1 &&  > testxx <aaa a $test testx'x' < aaa &&( cat hello <b && (<<c)<<d) && test");
}
