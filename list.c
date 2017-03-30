/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:37:38 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/03/30 14:54:10 by nahmed-m         ###   ########.fr       */
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
			if (father == NULL)
				*list = tmp2;
			else
				father->next = tmp2;
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

	tmp = (t_sort*)malloc(sizeof(t_sort));
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

void print_list(t_sort *list, int on)
{
	t_sort *tmp;

	tmp = list;
	while (tmp)
	{
	if (tmp->c != '?' && tmp->c != 'u' && ft_strcmp("", tmp->str))
		{
			if (on == 1)
			{
			if (tmp->value != 0)
				ft_printf("%016zx ", tmp->value);
			else
				ft_printf("%17 ");
			}
			else
			{
			if (tmp->value != 0)
				ft_printf("%08zx ", tmp->value);
			else
				ft_printf("%9 ");
			}
			ft_printf("%c ", tmp->c);
			ft_printf("%s\n", tmp->str);
		}
		tmp = tmp->next;
	}
}
