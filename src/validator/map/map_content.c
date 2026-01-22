/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 21:29:29 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct 
#include "utils.h" //read_file
#include "validator/config/config.h" //enum var
#include "libft.h" //len and strnstr
#include "free.h" //fre_content_asiigned.c
#include "map.h" //auxliar functions

char	**ft_get_map(char *file, t_error *error)
{
	int		idx;
	int		start_idx;
	int		last_idx;
	char	**content;
	char	**map;

	content = ft_read_file(file, error);
	if (content == NULL)
		return (NULL);
	start_idx = ft_get_map_start_idx(content);
	last_idx = ft_get_map_last_idx(start_idx, content);
	map = (char **)ft_calloc(1, sizeof(char *) * (last_idx - start_idx + 1 + 1));
	if (!map)
		return (ft_free_file_content(content), ft_set_error_system(error), NULL);
	idx = -1;
	while (start_idx <= last_idx)
	{
		map[++idx] = ft_strdup(content[start_idx]);
		if (!map[idx])
			return (ft_free_content_assigned(idx, map),
				ft_free_file_content(content),
				ft_set_error_system(error), NULL);
		start_idx++;
	}
	map[idx + 1] = NULL;
	return (ft_free_file_content(content), map);
}

void	ft_fill_spaces(char **map, t_error *error)
{
	int		i;
	size_t	len;
	int		chars_to_put;

	if (ft_has_error(error))
		return ;
	i = -1;
	len = 0;
	while (map[++i])
		if (ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
	i = -1;
	while (map[++i])
	{
		chars_to_put = len - ft_strlen(map[i]);
		map[i] = ft_replace_spaces(chars_to_put, map[i], error);
	}
}
