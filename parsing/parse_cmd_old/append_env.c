/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/13 13:04:17 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	my_strlen(char *str, char c)
{
	int	i;

	i = 0;


	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_getenv(char *str, int j)
{
	char	*key;
	char	*env;
	int		i;

	i = 0;
	key = malloc(my_strlen(str + j, ' ') + 1);
	if (!key)
		exit(1);
	while (str[j] && str[j] != ' ')
	{
		key[i++] = str[j++];
	}
	key[i] = '\0';
	//to change----------------------------------
	env = getenv(key+1);
	//--------------------------------------------
	return (env);
}

static char	*add_env(char *str, int *j)
{
	char 	*new_str;
	char	*env;
	int		keylen;
	int		i;
	int		k;

	i = 0;
	k = 0;
	keylen = my_strlen(str + *j, ' ');
	env = ft_getenv(str, *j);
	// if (!env)
	// 	keylen = 0;
	new_str = malloc(my_strlen(env, '\0') + my_strlen(str, '\0') - keylen + 1);
	if (!new_str)
		exit(1);
	while (i < *j)
		new_str[k++] = str[i++];
	while (env && *env)
		new_str[k++] = *(env++);
	while (str[i + keylen])
		new_str[k++] = str[(i++) + keylen];
	free(str);
	(*j) += keylen;
	return (new_str);
}

void	append_env(char **arr)
{
	int				i;
	int				j;
	t_check_quote	c_q;

	i = 0;
	c_q = (t_check_quote){0};
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			check_quotes(arr[i][j], &c_q);
			if (arr[i][j] == '$' && arr[i][j + 1] != '?' && \
			arr[i][j] && arr[i][j + 1] != ' ' && !c_q.is_sq)
				arr[i] = add_env(arr[i], &j);
			j++;
		}
		i++;
	}
}