/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:37:18 by azainabi          #+#    #+#             */
/*   Updated: 2024/05/11 11:17:48 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static int	check_path(t_tree *node, char *path, int perm, t_all *all)
{
	if (!path)
	{
		all->tmp = ft_strjoin("minibash: ", node->cmd[0], all);
		all->error = ft_strjoin(all->tmp, ": command not found", all);
		exit_stat(127, 1);
		return (1);
	}
	//explain this function
	is_a_dir(path, &perm);
	if (perm)
	{
		if (perm == 2)
		{
			all->tmp = ft_strjoin("minibash: ", path, all);
			all->error = ft_strjoin(all->tmp, ": is a directory", all);
		}
		else
		{
			all->tmp = ft_strjoin("minibash: ", path, all);
			all->error = ft_strjoin(all->tmp, ": Permission denied", all);
		}
		exit_stat(126, 1);
		return (1);
	}
	return (0);
}

static void	exe(t_tree *node, char **envp, char *path, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_write(FORK_ERROR, 2, 1);
		exit(1);
	}
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, node->cmd, envp) == -1)
		{
			perror("minibash: ");
			exit(1);
		}
	}
}

void	execute_single_command(t_tree *node, char **envp, t_all *all)
{
	char	*path;
	pid_t	pid;
	int		perm;
	int		stat;

	perm = 0;
	path = get_cmd_path(all, node->cmd[0]);
	if (check_path(node, path, perm, all))
		return ;
	exe(node, envp, path, &pid);
	waitpid(pid, &stat, 0);
	exit_stat(WEXITSTATUS(stat), 1);
}
