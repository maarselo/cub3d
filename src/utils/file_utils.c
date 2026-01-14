/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //gnl and ft_substr
#include <stdlib.h> //free

void	ft_free_content_assigned(int i, char **file_content)
{
	while (--i >= 0)
		free(file_content[i]);
	free(file_content);
}

char	*ft_get_clean_line(int *fd)
{
	int		len;
	char 	*line;
	char	*old_line;

	line = get_next_line(*fd);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		old_line = line;
		line = ft_substr(line, 0, len - 1);
		free(old_line);
		return (line);
	}
	else
		return(line);
}
