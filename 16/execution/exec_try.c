/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_try.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:52 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/17 17:44:56 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"


static void execute_parantheses(t_tree	*node, char **envp, t_all *all)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(node->input);
	old_stdout = dup(STDOUT_FILENO);
	printf("in %d out %d hd %d\n", node->input, node->output, node->here_doc);
	if (node->here_doc)
		dup2(node->here_doc, STDIN_FILENO);
	else
		dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	execute(node->left, envp, all);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);

}

static void	execute_and(t_tree *node, t_all *all)
{
	execute(node->left, all->envp, all);
	if (exit_stat(0, 0) == 0)
		execute(node->right, all->envp, all);
}

static void	execute_or(t_tree *node, t_all *all)
{
	execute(node->left, all->envp, all);
	if (exit_stat(0, 0) != 0)
		execute(node->right, all->envp, all);
}

int	execute(t_tree	*root, char **envp, t_all *all)
{
	if (!root)
		return (0);
	if (root->oper == PIPE)
		execute_pipe(root, envp, all);
	if (root->oper == PARENTHESES)
		execute_parantheses(root, envp, all);
	if (root->oper == OR )
		execute_or(root, all);
	if (root->oper == AND )
		execute_and(root, all);
	if (root->oper == NONE)
	{
		get_cmd_info(root, all);
		execute_command(root, envp, all);
	}
	return (0);
}
