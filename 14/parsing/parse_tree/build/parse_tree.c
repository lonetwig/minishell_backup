/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:39:46 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 12:14:06 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minibash.h"

void printTree(t_tree *root, int i, char *str, char **err) {
	if (root != NULL) 
	{
		if (root->oper)
			printf("in %d %s operator %d:(out %d in %d h_doc %d)\n\n",i ,str, root->oper, root->output, root->input, root->here_doc);
		if (root->cmd_str)
		{
			get_cmd_info(root, err);
			if (*err)
				printf("%s\n", *err);
			printf("in %d %s :(out %d in %d h_doc %d)\n",i, str, root->output, root->input, root->here_doc);
			while(*(root->cmd))
			{
				printf("%s \n",*(root->cmd));
				(root->cmd)++;
			}
			printf("\n");
		}
		printTree(root->left, i + 1, "left", err);
		printTree(root->right, i + 1, "right", err);
	}
}
//***************************************************
int    parse_tree(char *s, t_all *all, char **err)
{
	t_tree  *root;
	int		doc_i;

	root = NULL;
	doc_i = 0;
	if ((check_here_doc(s, err), *err) || \
		(check_q_p(s, err), *err) || \
		(check_opers(s, err), *err) || \
		(s = adjust_redirectionals(s, err), *err) || \
		(build_tree(s, (t_tree **[2]){&all->tree, &root}, err, &doc_i), *err))
		return (all->tree = root, 1);
	all->tree = root;
	printTree(root, 0, "start", err);
	return (0);
}
// int	main()
// {
// 	char	*error;
// 	t_all	all;

// 	error = NULL;

// 	parse_tree("test1 || <<hello test2 &&(test1 | test2 &&(hi))", &all, &error);
// 	remove_docs(&error);
// 	ft_open(NULL, 0, NULL, 1);
// 	ft_malloc(0, 1, NULL);


// 	parse_tree("<a ||hello 1", &all, &error);
// 	remove_docs(&error);
// 	ft_open(NULL, 0, NULL, 1);
// 	ft_malloc(0, 1, NULL);
// 	while (1);
// }