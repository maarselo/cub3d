/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_ignore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_ignore(char skip, char *str)
{
	int		i;
	int		j;
	int		real_len;
	char	*dup;

	i = -1;
	real_len = ft_strlen_ignore(skip, str);
	dup = (char *)malloc(sizeof(char) * (real_len + 1));
	if (!dup)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == skip)
			continue ;
		dup[j++] = str[i];
	}
	dup[j] = '\0';
	return (dup);
}
