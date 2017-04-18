/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:34:04 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/18 18:04:52 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

void	add_to_fat_list(t_fat_ptr **list, void *offset, cpu_type_t cputype)
{
	t_fat_ptr *ptr;
	
	ptr = *list;
	if (!*list)
	{
		ptr = (t_fat_ptr*)malloc(sizeof(t_fat_ptr));
		ptr->ptr = offset;
		ptr->cputype = little_to_big_32_uint(cputype);
		ptr->next = NULL;
		*list = ptr;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = (t_fat_ptr*)malloc(sizeof(t_fat_ptr));
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
		if (list->cputype == CPU_TYPE_I386)
			return (list->ptr);
		list = list->next;
	}
	return (NULL);
}

void	print_arch(int cputype)
{
	if (cputype == CPU_TYPE_I386)
		ft_printf("i386 :\n");
	else if (cputype == CPU_TYPE_X86_64)
		ft_printf("x86_64 :\n");
	else if (cputype == CPU_TYPE_ARM)
		ft_printf("arm :\n");
	else if (cputype == CPU_TYPE_ARM64)
		ft_printf("arm64 :\n");
	else if (cputype == CPU_TYPE_POWERPC)
		ft_printf("powerpc :\n");
	else
		ft_printf("unknow arch :\n");
}

void	print_fat_list(t_fat_ptr **list)
{
	t_fat_ptr	*freeme;

	while (*list)
	{
		print_arch((*list)->cputype);
		nm((char*)(*list)->ptr);
		ft_putchar('\n');
		freeme = *list;
		*list = (*list)->next;
		free(freeme);
	}
}


void	handler_fat(char *ptr)
{
	struct	fat_header *header;
	struct	fat_arch *arch;
	int		i;
	t_fat_ptr		*list;

	header = (struct fat_header*)ptr;
	arch = (void*)(ptr + sizeof(struct fat_header));
	list = NULL;
	i = 0;
	while (i < (int)little_to_big_32_uint(header->nfat_arch))
	{
		add_to_fat_list(&list, (void*)(ptr + little_to_big_32_uint(arch->offset)), arch->cputype);
		arch = (void*)arch + sizeof(struct fat_arch);

		i++;
	}
	if (verify_arch(list) != NULL && list)
		nm((char*)verify_arch(list));
	else if (list)
		print_fat_list(&list);
}
