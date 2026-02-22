/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_asigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_content_assigned(int i, char **file_content)
{
	while (--i >= 0)
		free(file_content[i]);
	free(file_content);
}
