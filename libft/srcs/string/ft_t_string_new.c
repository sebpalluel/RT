/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_string_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:59:23 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 17:09:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_string	*ft_t_string_new(uint32_t capacity)
{
	t_string	*string;

	if (!(string = (t_string*)malloc(sizeof(t_string))))
		exit(EXIT_FAILURE);
	string->capacity = capacity;
	if (!(string->string = (char*)malloc(sizeof(char) * (capacity + 1))))
		exit(EXIT_FAILURE);
	ft_memset(string->string, 0, capacity);
	string->len = 0;
	return (string);
}
