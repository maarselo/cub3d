/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "map.h" //auxliar functions
#include "libft.h" //ft_isspace
#include "free.h"

static void	ft_detect_invalid_chars(char **map, t_error *error)
{
	int		i;
	int		j;
	int		total_start_positions;

	i = -1;
	total_start_positions = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_isspace(map[i][j]))
				continue ;
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				total_start_positions++;
			else if (map[i][j] != '0' && map[i][j] != '1')
				return (ft_set_error_static(MAP_INVALID_CHARS, error,
						VALIDATOR));
		}
	}
	if (total_start_positions != 1)
		return (ft_set_error_static(MAP_MULTI_STARTS, error, VALIDATOR));
}

static int	ft_get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static void	ft_check_cell(int i, int j, char **map, t_error *error)
{
	if (ft_has_error(error))
		return ;
	if (i < 0 || i >= ft_get_map_height(map))
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
	if (j < 0 || j >= (int)ft_strlen(map[i]))
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
	if (map[i][j] == '-')
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
}

static void	ft_check_every_cell(char **map, t_error *error)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_isalpha(map[i][j]) || map[i][j] == '0')
			{
				ft_check_cell(i + 1, j, map, error);
				ft_check_cell(i, j + 1, map, error);
				ft_check_cell(i - 1, j, map, error);
				ft_check_cell(i, j - 1, map, error);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_map(char *file, t_error *error)
{
	char	**map;

	if (ft_has_error(error))
		return ;
	map = ft_get_map(file, error);
	ft_detect_invalid_chars(map, error);
	ft_fill_spaces(map, error);
	ft_check_every_cell(map, error);
	ft_free_file_content(map);
}
