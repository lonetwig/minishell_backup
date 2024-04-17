/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:34:59 by azainabi          #+#    #+#             */
/*   Updated: 2024/04/17 10:01:49 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	handle_redirections_exec(t_tree *node)
{
	if (node->here_doc != 0)
	{
		// write(2, "here\n", 5);
		dup2(node->here_doc, STDIN_FILENO);
		close(node->here_doc);
	}
	if (node->input != 0)
		dup2(node->input, STDIN_FILENO);
	if (node->output != 1)
		dup2(node->output, STDOUT_FILENO);
	
}

static void	command_err(char *path, char *type)
{
	ft_write("minibash: ", 2, 0);
	ft_write(path, 2, 0);
	ft_write(type, 2, 1);
	exit_stat(127, 1);
	exit(127);
}

static void	execute_command_cp(t_tree *node, char **envp, t_all *all)
{
	char	*path;

	path = get_cmd_path(all, node->cmd[0]);
	if (!path)
		command_err(node->cmd[0], ": command not found");
	if (is_a_dir(path))
		command_err(path, ": is a directory");
	if (execve(path, node->cmd, all->envp) == -1)
	{
		perror("");
		exit(111);
	}
}

void	execute_command(t_tree *node, char **envp, t_all *all)
{
	int		id;
	int		status;

	handle_redirections_exec(node);
	if (check_builtins(node, all))
		return ;
	signal(SIGINT, SIG_DFL);
	id = fork();
	if (id == -1)
	{
		perror("");
		exit(14);
	}
	if (id == 0)
		execute_command_cp(node, envp, all);
	else
	{
		waitpid(id, &status, 0);
		exit_stat(WEXITSTATUS(status), 1);
	}
}
