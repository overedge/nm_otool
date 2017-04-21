/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:37:38 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/20 23:16:24 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	sort_list(t_sort **list)
{
	t_sort *tmp;
	t_sort *tmp2;
	t_sort *father;

	father = NULL;
	tmp = *list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->str, tmp->next->str) > 0)
		{
			tmp2 = tmp->next;
			tmp->next = tmp2->next;
			tmp2->next = tmp;
			(father == NULL) ? (*list = tmp2) : 0;
			(father != NULL) ? (father->next = tmp2) : 0;
			tmp = *list;
			father = NULL;
		}
		else
		{
			father = tmp;
			tmp = tmp->next;
		}
	}
}

void	add_list(unsigned long long value, char c, char *str, t_sort **list)
{
	t_sort *tmp;
	t_sort *tmp2;

	if ((tmp = (t_sort*)malloc(sizeof(t_sort))) == NULL)
		ft_error("MALLOC ERROR \n");
	tmp->value = value;
	tmp->c = c;
	tmp->str = strdup(str);
	tmp->next = NULL;
	if (!*list)
		*list = tmp;
	else
	{
		tmp2 = *list;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

void	print_list(t_sort *list, int on)
{
	while (list)
	{
		if (list->c != '?' && list->c != 'u' && ft_strcmp("", list->str))
		{
			if (on == 1)
			{
				if (list->value != 0 || (list->value == 0 && list->c == 'T'))
					ft_printf("%016zx ", list->value);
				else
					ft_printf("%17 ");
			}
			else
			{
				if (list->value != 0 || (list->value == 0 && list->c == 'T'))
					ft_printf("%08zx ", list->value);
				else
					ft_printf("%9 ");
			}
			ft_printf("%c ", list->c);
			ft_printf("%s\n", list->str);
		}
		list = list->next;
	}
}

void	del_list(t_sort **list)
{
	t_sort *freeme;

	while (*list)
	{
		ft_strdel(&(*list)->str);
		freeme = *list;
		*list = (*list)->next;
		free(freeme);
	}
}
