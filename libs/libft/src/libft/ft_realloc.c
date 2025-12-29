/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:51:58 by mvillavi          #+#    #+#             */
/*   Updated: 2025/12/29 15:51:59 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	char	*new_ptr;
	int		bytes_to_copy;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (old_size < new_size)
		bytes_to_copy = old_size;
	else
		bytes_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, bytes_to_copy);
	return (free(ptr), new_ptr);
}
