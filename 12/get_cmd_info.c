/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:15:38 by ealislam          #+#    #+#             */
/*   Updated: 2024/03/07 11:11:10 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minibash.h"

int	get_cmd_info(t_tree *branch)
{
	char	**pre_env_arr;
	char	*str;
	char	**err;

	*err = NULL;
	str = branch->cmd_str;
	pre_env_arr = split_by_space(str, err);
	get_environment(&str, err);
	branch->cmd = split_by_space(str, err);
	get_wildcard(branch->cmd, err);
	branch->input = get_input_output(branch->cmd, 0, pre_env_arr, err);
	branch->output = get_input_output(branch->cmd, 1, pre_env_arr, err);
	branch->here_doc = get_here_doc(str, &branch->input, branch->doc_i, err);
	if (*err)
		return (ft_write(err, 2), 1);
	return (0);
}
