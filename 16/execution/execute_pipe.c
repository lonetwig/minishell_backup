/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:30:08 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/17 18:02:51 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	execute_left(t_tree *node, int *fd, char **envp, t_all *all)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(node, envp, all);
	exit(0);
}

static void	perror_and_exit()
{
	perror("");
	exit(1);
}

void	execute_pipe(t_tree *node, char **envp, t_all *all)
{
	int		fd[2];
	pid_t 	pid1;
	pid_t 	pid2;
	int		old_nodeInput;

	old_nodeInput = dup(node->input);
	if (pipe(fd) == -1)
		perror_and_exit();
	pid1 = fork();
	if (pid1 == -1)
		perror_and_exit();
	dup2(fd[0], node->input);	
	if (pid1 == 0)
		execute_left(node->left, fd, envp, all);
	else 
	{
		close(fd[0]);
		close(fd[1]);
		execute(node->right, envp, all);
		waitpid(pid1, NULL, 0);
		dup2(old_nodeInput, node->input);
		// exit_stat(0, 1);
	}
}
