/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "map.h" //auxliar functions
#include "libft.h" //ft_isspace

void	ft_detect_invalid_chars(char **map, t_error *error)
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
				return (ft_set_error_static(MAP_INVALID_CHARS, error, VALIDATOR));
		}
	}
	if (total_start_positions != 1)
		return (ft_set_error_static(MAP_MULTI_STARTS, error, VALIDATOR));
}

void	ft_get_start_position(int *i, int *j, char **map)
{
	*i = -1;
	while (map[++(*i)])
	{
		*j = -1;
		while (map[*i][++(*j)])
		{
			if (map[*i][*j] == 'N' || map[*i][*j] == 'S'
				|| map[*i][*j] == 'W' || map[*i][*j] == 'E')
				return ;
		}
	}
}

int	ft_get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

#include <stdio.h>
void	ft_check_walls(int i, int j, char **map, t_error *error)
{
	int	max_height;
	int	max_len;

	if (ft_has_error(error))
		return ;
	max_height = ft_get_map_height(map);
	max_len = ft_strlen(map[i]);
	if (map[i] && (map[i][j] == '1' || map[i][j] == 'X'))
		return ;
	if (i <= 0 || i >= max_height || j <= 0 || j >= max_len)
	// {
		// printf("valor max_height: %d\n valor lmmax_len: %d\ncalor i= %d\nvalor de j=%d\n",max_height, max_len, i, j);
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
	// }
	map[i][j] = 'X';
}

#include <stdio.h>
void	ft_check_map(char *file, t_error *error)
{
	int		i;
	int		j;
	char	**map;

	if (ft_has_error(error))
		return ;
	map = ft_get_map(file, error);
	ft_detect_invalid_chars(map, error);
	ft_get_start_position(&i, &j, map);
	ft_check_walls(i, j, map, error);
}
