/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:20:39 by ealislam          #+#    #+#             */
/*   Updated: 2024/04/17 15:39:42 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minibash.h"

static void	minibash_readline(char **str, t_all *all)
{
	*str = NULL;
	if (!all->error && !exit_stat(0, 0) )
		*str = readline("minibash 🙌 > ");
	else
	{
		if (all->error)
			ft_write(all->error, 2, 1);
		*str = readline("minibash 💀 > ");
		all->error = NULL;
	}
	if (*str && **str)
		add_history(*str);
	if (*str && !**str)
		free(*str);
	if (!*str)
		printf("exit\n");
}

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		exit_stat(1, 1);
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_all	all;

	str = NULL;
	all.error = NULL;
	all.env = parse_env(envp, &all);
	all.envp = linked_list_to_arr(&all);
	while (1)
	{
		all.tree = NULL;
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, SIG_IGN);
		minibash_readline(&str, &all);
		if (!str)
			break ;
		if (!str[0])
			continue ;
		parse_tree(str, &all);
		free (str);
		if (all.error)
			continue ;
		execute(all.tree, all.envp, &all);
		remove_docs(&all);
		ft_open(NULL, 0, NULL, 1);
		ft_malloc(0, 1, NULL);
	}
	ft_malloc_permanent(0, 1, NULL);
}
