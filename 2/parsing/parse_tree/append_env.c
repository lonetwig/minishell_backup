/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/16 10:54:09 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	my_strlen(char *str, char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j] && !(str[i] == '$' && i == 0))
				return (i);
			if (i == 0 && str[i] == '$' && str[i + 1] == delim[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

static char	*ft_getenv(char *str, int j)
{
	char	*key;
	int		key_len;
	char	*env;
	int		i;

	i = 0;
	key_len = my_strlen(str + j, "$ \"'");
	key = malloc(key_len + 1);
	if (!key)
		exit(1);
	while (str[j] && i < key_len)
		key[i++] = str[j++];
	key[i] = '\0';
	// printf("%s %d\n",key, key_len);
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
	keylen = my_strlen(str + *j, "$ \"'");
	env = ft_getenv(str, *j);
	new_str = malloc(my_strlen(env, "\0") + my_strlen(str, "\0") - keylen + 1);
	if (!new_str)
		exit(1);
	while (i < *j)
		new_str[k++] = str[i++];
	while (i++ && env && *env)
		new_str[k++] = *(env++);
	while (str[i])
		new_str[k++] = str[(i++)];
	new_str[k] = '\0';
	//add it back ----------------------------------
	// free(str);
	(*j) += keylen;
	return (new_str);
}

void	append_env(char **s)
{
	int				j;
	t_check_quote	c_q;
	char			c;
	char			next_c;

	c_q = (t_check_quote){0};
	j = 0;
	while ((*s)[j])
	{
		c = (*s)[j];
		next_c = (*s)[j + 1];
		check_quotes(c, &c_q);
		if (c == '$' && next_c != '?' && next_c != ' ' && !c_q.is_sq)
		{
			(*s) = add_env((*s), &j);
			continue;
		}
		j++;
	}
}

