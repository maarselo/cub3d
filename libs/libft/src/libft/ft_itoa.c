/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:43:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 18:03:49 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		digits;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	digits = ft_count(n);
	ptr = (char *)ft_calloc(1, (digits + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[digits] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	while (--digits >= 0)
	{
		if (ptr[digits] == '-')
			break ;
		ptr[digits] = ('0' + (n % 10));
		n /= 10;
	}
	return (ptr);
}
