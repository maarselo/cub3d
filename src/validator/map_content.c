/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "errorctx.h" //struct 
#include "utils.h" //read_file
#include "validator/config.h" //enum var
#include "../../libs/libft/include/libft.h" //len and strnstr
#include "free.h" //fre_content_asiigned.c

int	ft_get_map_start_idx(char **content)
{
	int		i;
	int		j;
	int		cfg_found;

	i = -1;
	cfg_found = 0;
	while (content[++i] && cfg_found < CONFIG_COUNT)
	{
		if (ft_isspace_str(content[i]))
			continue; ;
		j = -1;
		while (g_config_string[++j])
		{
			if (ft_strnstr(content[i], g_config_string[j],
					ft_strlen(content[i])))
			{
				cfg_found++;
				break ;
			}
		}
	}
	while (content[i] && ft_isspace_str(content[i]))
		i++ ;
	return (i);
}

int	ft_get_map_last_idx(int start_idx, char **content)
{
	int	idx;
	int	last_idx;

	idx = start_idx;
	while (content[idx])
	{
		if (ft_isspace_str(content[idx]))
		{
			idx++;
			continue ;
		}
		else
			last_idx = idx;
		idx++;
	}
	return (last_idx);
}

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
