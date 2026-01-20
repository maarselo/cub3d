/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_lastc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_get_lastc(char *str)
{
	int		i;
	char	tmp;

	i = -1;
	tmp = 0;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			continue ;
		else if (ft_isprint(str[i]))
			tmp = str[i];
	}
	return (tmp);
}
