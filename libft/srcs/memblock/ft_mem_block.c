/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 16:02:35 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 17:05:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Create a memory container for the data
*/

void				*create_block(size_t *size, const size_t limit)
{
	void			*ptr;

	while (!(ptr = malloc(*size)))
	{
		*size >>= 2;
		if (*size < limit)
			return (NULL);
	}
	return (ptr);
}

/*
** Create a mem_block quite litterally...
*/

t_mem_block			*create_mem_block(size_t size)
{
	t_mem_block		*block;

	if (!(block = (t_mem_block *)malloc(sizeof(t_mem_block))))
		return (NULL);
	block->block_size = size;
	if (!(block->ptr = create_block(&(block->block_size), 256)))
		return (NULL);
	block->index = 0;
	block->next = NULL;
	return (block);
}

/*
** Expand the mem_block, for example went you don't have space for an object
*/

t_mem_block			*expand_mem_block(t_mem_block *b, size_t blocks)
{
	while (b->next)
		b = b->next;
	while (blocks > 0)
	{
		b->next = create_mem_block(b->block_size << 1);
		blocks--;
		b = (b->next) ? b->next : b;
	}
	return (b);
}

/*
** Will store a data in memory, if it can't the program will crash anyway
** or earth will be no more...
*/

void				*push_to_mem_block(t_mem_block *b, void *p, size_t size)
{
	void			*t;

	while (b->next)
	{
		if ((b->index) + size <= b->block_size)
		{
			t = (void*)(((char*)b->ptr) + (b->index));
			b->index += size;
			ft_memcpy(t, p, size);
			return (t);
		}
		b = b->next;
	}
	if ((b->index) + size > b->block_size)
		b = expand_mem_block(b, 1);
	t = (void*)(((char*)b->ptr) + (b->index));
	b->index += size;
	ft_memcpy(t, p, size);
	return (t);
}

/*
** Attempt to store a data in memory, if failed return NULL
*/

void				*store_to_mem_block(t_mem_block *b, void *data, size_t size)
{
	void			*t;

	t = NULL;
	if (b->index + size <= b->block_size)
	{
		t = (void*)(((char*)b->ptr) + b->index);
		b->index += size;
		ft_memcpy(t, data, size);
	}
	return (t);
}
