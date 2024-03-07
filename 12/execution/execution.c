/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:25:54 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 11:30:38 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	normal_execution(t_all *all, t_tree *tree)
{
	//execve
	//
}

void	pipe_execution(t_all *all, t_tree *tree)
{
	//pipex
}

int	handle_paren(t_all	*all, t_tree *tree)
{
    int original_input;
    int original_output;

	if (tree->oper !=PARENTHESES)
		return (0);
    original_input = dup(0);
    original_output = dup(1);
	if (tree->input == -1)
		return (1);
	dup2(tree->input, 0);
	dup2(tree->output, 1);
	execution(all, tree->left, NONE);
    dup2(original_input, 0);
    dup2(original_output, 1);
	close(original_input);
    close(original_output);
	return (1);
}

void	execution(t_all	*all, t_tree *tree, e_oper exec_mode)
{
	if (!tree || handle_paren(all, tree))
		return ;
	if (tree->cmd_str && exec_mode != PIPE && get_cmd_info(tree))
		normal_execution(all, tree);
	if (tree->cmd_str && exec_mode == PIPE && get_cmd_info(tree))
		pipe_execution(all, tree);
	execution(all, tree->left, tree->oper);
	if (tree->oper == AND && all->status)
		return ;
	if (tree->oper == OR && all->status)
		return ;
	execution(all, tree->right, tree->oper);
}
