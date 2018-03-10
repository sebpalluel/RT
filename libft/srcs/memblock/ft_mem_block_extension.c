/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_block_extension.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 18:32:34 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 17:04:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "../../includes/libft.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
#pragma clang diagnostic ignored "-Wpointer-arith"

/*
** This function will allocate you a element of the size you wanted except if
** this element would have to be of a size inferior of the double of the last
** block of the memblock.
** So you don't have to use push_to_mem_block that need data to be created.
*/

void					*allocate_elem_on_mem_block(t_mem_block *b
		, uint32_t size)
{
	void				*ptr;

	while (b->next)
	{
		if (b->index + size <= b->block_size)
		{
			ptr = (void*)(((char*)b->ptr) + b->index);
			b->index += size;
			return (ptr);
		}
		b = b->next;
	}
	if ((b->block_size << 1) < size)
		ft_error_exit(1, &(MB_ERR_E_BIG), EXIT_FAILURE);
	if (b->block_size < b->index + size)
		b = expand_mem_block(b, 1);
	ptr = (void*)(((char*)b->ptr) + b->index);
	b->index += size;
	return (ptr);
}

/*
** This function will allocate you a element of the size you want no matter what
*/

static inline uint32_t	get_next_2_pow(uint32_t v)
{
	--v;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	return (++v);
}

void					*force_allocate_elem_on_mem_block(t_mem_block *b
		, uint32_t size)
{
	void				*ptr;

	while (b->next)
	{
		if (b->index + size <= b->block_size)
		{
			ptr = (void*)(((char*)b->ptr) + b->index);
			b->index += size;
			return (ptr);
		}
		b = b->next;
	}
	if (b->block_size < size)
	{
		b->next = create_mem_block(get_next_2_pow(size));
		b = b->next;
	}
	ptr = (void*)(((char*)b->ptr) + b->index);
	b->index += size;
	return (ptr);
}

/*
** WARNING THIS FUNCTION IS NOT TO BE USED
** you've been warned...
**
** This function will remove an element if found in the memblock.
** This method is totally unsafe and will probably fuck up your pointer to
** the data which is present after on the block.
*/

void					remove_elem_of_mem_block(t_mem_block *b, void *ptr
		, uint32_t size)
{
	while (b)
	{
		if ((b->ptr <= ptr) && (ptr < (b->ptr + b->block_size)))
		{
			ft_memcpy(ptr, (ptr + size), (b->block_size - b->index));
			b->index -= size;
			return ;
		}
		b = b->next;
	}
}

#pragma clang diagnostic pop
