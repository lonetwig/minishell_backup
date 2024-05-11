/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:20:39 by ealislam          #+#    #+#             */
/*   Updated: 2024/05/11 14:26:53 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minibash.h"

static void	init_var(t_all *all, char **envp, char **argv, int argc)
{
	(void)argc;
	(void)argv;
	all->original_in = dup(STDIN_FILENO);
	all->original_out = dup(STDOUT_FILENO);
	all->error = NULL;
	all->env = parse_env(envp, all);
	all->envp = linked_list_to_arr(all);
}

static void	minibash_readline(char **str, t_all *all)
{
	char	*input;

	input = NULL;
	if (!all->error && !exit_stat(0, 0))
		input = readline("minibash 🙌 > ");
	else
	{
		if (all->error)
			ft_write(all->error, 2, 1);
		input = readline("minibash 💀 > ");
		all->error = NULL;
	}
	if (!input)
		*str = NULL;
	if (input)
	{
		*str = ft_strdup(input, all);
		free(input);
	}
}

static int	input_loop(t_all *all, char *str)
{
	//explain name 
	set_delim(0, 1);
	//explain why you overwrite the signal on each loop and not only once
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	all->tree = NULL;
	minibash_readline(&str, all);
	if (!str)
	{
		printf("exit\n");
		return (2);
	}
	add_history(str);
	//explain why used here (my guess you dont want to execute an empty input)
	get_environment(all, &str);
	if (str[0] == 0)
	{
		free(str);
		return (1);
	}
	parse_tree(str, all);
	if (all->error || set_delim(0, 0))
	{
		free(str);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_all	all;
	int		input;

	str = NULL;
	//explain the name
	input = 0;
	rl_catch_signals = 0;
	init_var(&all, envp, argv, argc);
	while (1)
	{
		input = input_loop(&all, str);
		if (input == 1)
			continue ;
		else if (input == 2)
			break ;
		if (!all.tree->left && !all.tree->right && all.tree->oper == NONE)
			execute_one_command(&all);
		else
			execute(all.tree, all.envp, &all);
		free (str);
		remove_docs(&all);
		ft_open(NULL, 0, NULL, 1);
	}
	ft_malloc(0, 1, NULL);
}
