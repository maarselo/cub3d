/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_content.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h" //ft_strtrim

void	ft_remove_map(int last_cfg_line, char **file_content)
{
	int	current_line;

	current_line = last_cfg_line;
	if (!file_content[current_line])
		return ;
	while (file_content[current_line])
	{
		free(file_content[current_line]);
		file_content[current_line++] = NULL;
	}
}

void	ft_strtrim_spaces(char **split)
{
	int		idx;
	char	*tmp;

	idx = -1;
	while (split[++idx])
	{
		tmp = split[idx];
		split[idx] = ft_strtrim(split[idx], " ");
		free(tmp);
	}
}
