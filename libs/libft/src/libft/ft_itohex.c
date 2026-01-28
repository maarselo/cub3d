/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:24:33 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/28 14:55:04 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itohex(int n)
{
	char 			*base;
	unsigned int	tmp;
	unsigned int	num;
	int				len;
	char			*str;

	num = (unsigned int)n;
	tmp = num;
	len = 1;
	base = "0123456789ABCDEF";
	while (tmp >= 16)
	{
		tmp /= 16;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[num % 16];
		n /= 16;
	}
	return (str);
}
