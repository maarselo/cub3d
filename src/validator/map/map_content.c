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

static int	ft_get_map_start_idx(char **content)
{
	int		i;
	int		j;
	int		cfg_found;

	i = -1;
	cfg_found = 0;
	while (content[++i] && cfg_found < CONFIG_COUNT)
	{
		if (ft_isspace_str(content[i]))
			continue ;
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

static int	ft_get_map_last_idx(int start_idx, char **content)
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
	if (!content)
		return (NULL);
	start_idx = ft_get_map_start_idx(content);
	last_idx = ft_get_map_last_idx(start_idx, content);
	map = (char **)ft_calloc(1, sizeof(char *) * (last_idx - start_idx + 2));
	if (!map)
		return (ft_free_file_content(content),
			ft_set_error_system(error), NULL);
	idx = -1;
	while (start_idx <= last_idx)
	{
		map[++idx] = ft_strdup(content[start_idx++]);
		if (!map[idx])
			return (ft_free_content_assigned(idx, map),
				ft_free_file_content(content),
				ft_set_error_system(error), NULL);
	}
	return (map[idx + 1] = NULL, ft_free_file_content(content), map);
}

static char	*ft_replace_spaces(int chars, char *str, t_error *error)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = (char *)malloc(sizeof(char) * chars + 1);
	if (!str1)
		return (ft_set_error_system(error), NULL);
	i = -1;
	while (++i < chars)
		str1[i] = '-';
	str1[i] = '\0';
	str2 = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!str2)
		return (ft_set_error_system(error), NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			str2[i] = '-';
		else
			str2[i] = str[i];
	}
	str2[i] = '\0';
	return (free(str), ft_strjoin(str2, str1));
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
