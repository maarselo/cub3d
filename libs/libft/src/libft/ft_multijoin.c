/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:52:26 by mvillavi          #+#    #+#             */
/*   Updated: 2025/12/29 15:52:27 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_multijoin(int total_str, ...)
{
	int		i;
	int		previous_len;
	char	*tmp_str;
	char	*strjoin;
	va_list	va;

	va_start(va, total_str);
	strjoin = ft_strdup(va_arg(va, char *));
	if (!strjoin)
		return (va_end(va), NULL);
	i = 1;
	while (++i <= total_str)
	{
		tmp_str = va_arg(va, char *);
		previous_len = ft_strlen(strjoin);
		strjoin = (char *)ft_realloc(strjoin, previous_len, previous_len
				+ ft_strlen(tmp_str) + 1);
		if (!strjoin)
			return (va_end(va), NULL);
		ft_strlcpy(strjoin + previous_len, tmp_str, ft_strlen(tmp_str) + 1);
	}
	va_end(va);
	return (strjoin);
}
