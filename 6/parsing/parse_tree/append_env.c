/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:30 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/21 12:12:56 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minibash.h"

static int	my_strlen(char *str, char *delim)
{
	int	i;
	int	j;
	int	cdt_dolar_in_begining;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (delim[j])
		{
			cdt_dolar_in_begining = (str[i] == '$' && i == 0);
			if (str[i] == delim[j] && !(cdt_dolar_in_begining))
				return (i);
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
	//to change----------------------------------
	env = getenv(key+1);
	//--------------------------------------------
	return (env);
}

static char	*add_env(char *str, int i)
{
	char 	*new_str;
	char	*env;
	int		keylen;
	int		j;
	int		k;

	j = 0;
	k = 0;
	keylen = my_strlen(str + i, "$ \"'");
	env = ft_getenv(str, i);
	new_str = malloc(my_strlen(env, "\0") + my_strlen(str, "\0") - keylen + 2);
	if (!new_str)
		exit(1);
	while (j < i)
		new_str[k++] = str[j++];
	while (env && *env)
		new_str[k++] = *(env++);
	new_str[k++] = ' ';
	j+= keylen;
	while (str[j])
		new_str[k++] = str[j++];
	new_str[k] = '\0';
	//add it back ----------------------------------
	return (new_str);
}

void	append_env(char **s)
{
	int				i;
	t_check_quote	c_q;
	char			c;
	char			next_c;

	c_q = (t_check_quote){0};
	i = 0;
	while ((*s)[i])
	{
		c = (*s)[i];
		next_c = (*s)[i + 1];
		check_quotes(c, &c_q);
		if (c == '$' && next_c != '?' && next_c != ' ' && !c_q.is_sq)
			*s = add_env((*s), i);
		i++;
	}
}

