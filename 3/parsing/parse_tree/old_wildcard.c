/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealislam <ealislam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:30:04 by ealislam          #+#    #+#             */
/*   Updated: 2024/02/19 14:29:33 by ealislam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//split
//check wildcare with strnstr
//append to the final str
//repeat for each entry in the spliter string



// #include "../../includes/minibash.h"

// // ***c*o***

// //conditions.c
// //**ons*.c**

// //look for 
// // check_q_p.c

// int	exist_cdt(char c)
// {
// 	if (c && c != ' ' && c != '\n')
// 		return (1);
// 	return (0);
// }

// int	compare_str(char *str, char *patt)
// {
// 	char	*original_patt;
// 	original_patt = patt;

// 	if (*patt != '*' && *str != *patt)
// 		return (0);
// 	// printf("0 s = %s  p = %s\n", str, patt);
// 	if (*patt == '*')
// 	{
// 		while (*patt == '*')
// 			patt++;
// 		while (exist_cdt(*str) && *str != *patt)
// 			str++;
// 	}
// 	// printf("1 s = %s  p = %s\n", str, patt);
// 	// printf("%c %c\n",*patt,*str);
// 	while (exist_cdt(*patt) && *patt == *str)
// 	{
// 		str++;
// 		patt++;
// 	}
// 	// printf("2 s = %s  p = %s\n", str, patt);
// 	if (exist_cdt(*str) && *patt == '*')
// 		return (compare_str(str, patt));
// 	// printf("a\n");
// 	if (exist_cdt(*str) && exist_cdt(*patt) && *patt != *str)
// 		return (compare_str(str, original_patt));
// 	// printf("b\n");
// 	if (*patt == '*')
// 		return (compare_str(str, patt));
// 	if (!exist_cdt(*patt) && !exist_cdt(*str))
// 		return (1);
// 	// if (!exist_cdt(*patt))
// 	// 	return (1);
// 	// printf("finished with fail\n");
// 	// printf("(%c %c\n)",*patt,*str);
// 	return (0);
// 	// if (exist_cdt(*patt && *patt != '*'))
// 	// 	return (compare_str(str, original_patt));
// }

// //conditions.c
// //**ons*

// // int	compare_str(char *str, char *patt)
// // {
// // 	while (exist_cdt(*str))
// // 	{
// // 		if (*patt == '*')
// // 		{
// // 			// printf("0[%s]{%s}\n", str, patt);
// // 			while (*patt == '*')
// // 				patt++;
// // 			if(*patt == '.' && patt[1] == '*')
// // 			{
// // 				patt++;
// // 				continue ;
// // 			}
// // 			// printf("1[%s]{%s}\n", str, patt);
// // 			while (*str && *str != *patt)
// // 				str++;
// // 			// printf("2[%s]{%s}\n", str, patt);
// // 			// if (*str == '\0' && *patt == '\0')
// // 			// 	return (1);
// // 		}
// // 		if (*str != *patt && exist_cdt(*patt))
// // 			return (0);
	
// // 		if (*patt && exist_cdt(*str))
// // 			patt++;
// // 		if (exist_cdt(*str))
// // 			str++;
// // 		if (!*patt && *str)
// // 			return (0);
// // 		printf("3[%s]{%s}\n", str, patt);
// // 	}
// // 	while (*patt == '*')
// // 		patt++;
// // 	if (*patt == ' ' || *patt == '\n' || *patt == '\0')
// // 		return (1);
// // 	// printf("failed\n");
// // 	return (0);
// // }

			
// char	*append_pattern(char *str, char *file_str, int start, int *add)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;

// 	i = 0;
// 	j = 0;
// 	(*add) += ft_strlen(file_str) + 1;
// 	new_str = malloc (ft_strlen(file_str) + start + 2);
// 	while (i < start)
// 	{
// 		new_str[i] = str[i];
// 		i++;
// 	}
// 	while (file_str[j])
// 	{
// 		new_str[i + j] = file_str[j];
// 		j++;
// 	}
// 	new_str[i + j] = ' ';
// 	new_str[i + j + 1] = '\0';
// 	// printf("1111111%s1111111\n",new_str);
// 	return (new_str);
// }

// char	*compare_pattern(char *str, t_wildcard *w, t_str_list *files)
// {

// 	char		*end_of_str;
// 	char		*pattern;
// 	int			add;

// 	add = 0;
// 	// printf("[[%d]]\n\n", w->last_space);
// 	// w->last_space++;
// 	pattern = str + w->last_space;
// 	end_of_str = ft_strdup(str + w->next_space);
// 	// printf("{{%s}}\n",str);
// 	while (files)
// 	{
// 		if (compare_str(files->str, pattern))
// 			str = append_pattern(str, files->str, w->last_space + add, &add);
// 		files = files->next;
// 	}
// 	if (add)
// 		str = append_pattern(str, end_of_str, w->last_space + add - 1, &add);
// 	return (str);
// }

// char	*get_patterns(t_str_list *all_files, char *str)
// {
// 	t_wildcard	w;

// 	w = (t_wildcard){0};
// 	// if (str[0] != ' ')
// 	// 	w.last_space = -1;
// 	while (1)
// 	{
// 		check_quotes(str[w.i], &w.c_q);
// 		if (!exist_cdt(str[w.i]) && !cond_q(w.c_q))
// 			w.next_space = w.i;
// 		if (str[w.i] == '*' && !cond_q(w.c_q))
// 			w.wildcard_found = 1;
// 		if (w.next_space)
// 		{
// 			// printf("{{%s %d %d}}\n", str + w.last_space, w.last_space, w.wildcard_found);
// 			if (w.wildcard_found)
// 			{
// 				str = compare_pattern(str, &w, all_files);
// 				w.last_space = w.i;
// 			}
// 			// if (w.i >= 1)
// 			w.next_space = 0;
// 			w.wildcard_found = 0;
// 		}
// 		if (!str[w.i])
// 			break ;
// 		w.i++;
// 	}
// 	return (str);
// }

// void	wildcard(char **str)
// {
// 	t_str_list	*all_files;

// 	all_files = NULL;
// 	get_files(&all_files);
// 	*str = get_patterns(all_files, *str);
// }

// int main()
// {
// 	// char *str = "c*o*.c *o.p.c ***o*c*.c ****** c*******o*.c c*****. c*.o c***on.c ****a.out** *.*****t" ;
// 	char *str = " ****a.out " ;
// 	// char *str =  "****a.out**" ;
// 	wildcard(&str);
// 	printf("%s\n",str);
// 	// printf("%d\n",compare_str("a.out",str));
// }