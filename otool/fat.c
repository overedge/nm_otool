/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:34:04 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:10:13 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	add_to_fat_list(t_fat_ptr **list, void *offset, cpu_type_t cputype)
{
	t_fat_ptr *ptr;

	ptr = *list;
	if (!*list)
	{
		if ((ptr = (t_fat_ptr*)malloc(sizeof(t_fat_ptr))) == NULL)
			ft_error("MALLOC ERROR\n");
		ptr->ptr = offset;
		ptr->cputype = little_to_big_32_uint(cputype);
		ptr->next = NULL;
		*list = ptr;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		if ((ptr->next = (t_fat_ptr*)malloc(sizeof(t_fat_ptr))) == NULL)
			ft_error("MALLOC ERROR\n");
		ptr = ptr->next;
		ptr->ptr = offset;
		ptr->cputype = little_to_big_32_uint(cputype);
		ptr->next = NULL;
	}
}

void	*verify_arch(t_fat_ptr *list)
{
	while (list)
	{
		if (list->cputype == CPU_TYPE_X86_64)
			return (list->ptr);
		list = list->next;
	}
	return (NULL);
}

void	print_arch(int cputype)
{
	if (cputype == CPU_TYPE_I386)
		ft_printf("i386):\n");
	else if (cputype == CPU_TYPE_X86_64)
		ft_printf("x86_64):\n");
	else if (cputype == CPU_TYPE_ARM)
		ft_printf("arm):\n");
	else if (cputype == CPU_TYPE_ARM64)
		ft_printf("arm64):\n");
	else if (cputype == CPU_TYPE_POWERPC)
		ft_printf("ppc):\n");
	else
		ft_printf("unknow arch):\n");
}

void	print_fat_list(t_fat_ptr **list, char *argv)
{
	t_fat_ptr	*freeme;

	while (*list)
	{
		ft_printf("%s (architecture ", argv);
		print_arch((*list)->cputype);
		otool((char*)(*list)->ptr, NULL);
		ft_putchar('\n');
		freeme = *list;
		*list = (*list)->next;
		free(freeme);
	}
}

void	handler_fat(char *ptr, char *argv)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					i;
	t_fat_ptr			*list;

	header = (struct fat_header*)ptr;
	arch = (void*)(ptr + sizeof(struct fat_header));
	list = NULL;
	i = 0;
	while (i < (int)little_to_big_32_uint(header->nfat_arch))
	{
		add_to_fat_list(&list, (void*)(ptr + \
					little_to_big_32_uint(arch->offset)), arch->cputype);
		arch = (void*)arch + sizeof(struct fat_arch);
		i++;
	}
	if (verify_arch(list) != NULL && list)
	{
		otool((char*)verify_arch(list), argv);
		delete_fat_list(&list);
	}
	else if (list)
		print_fat_list(&list, argv);
}
