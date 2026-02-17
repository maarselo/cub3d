/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //ft_isspace
#include "errorctx.h" //struct
#include "validator/map/map_validator.h" //hepers func

void	ft_detect_invalid_chars(char **map, t_error *error)
{
	int		i;
	int		j;
	int		total_start_positions;

	if (ft_has_error(error))
		return ;
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
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '|' && map[i][j] != '_')
				return (ft_set_error_static(MAP_INVALID_CHARS, error,
						VALIDATOR));
		}
	}
	if (total_start_positions != 1)
		return (ft_set_error_static(MAP_MULTI_STARTS, error, VALIDATOR));
}

void	ft_check_doors(char **map, t_error *error)
{
	int	i;
	int j;

	if (ft_has_error(error))
		return ;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '-')
			{
				ft_check_any_doors(i + 1, j, map, error);
				ft_check_any_doors(i - 1, j, map, error);
				ft_check_any_doors(i, j + 1, map, error);
				ft_check_any_doors(i, j - 1, map, error);
			}
			if (ft_has_error(error))
				return ;
			if (map[i][j] == '|' || map[i][j] == '_')
			{
				if (map[i][j] == '|' && (map[i - 1][j] != '1' || map[i + 1][j] != '1'))
					return (ft_set_error_static(MAP_DOORS_NOT_BETWEEN_WALLS, error, VALIDATOR));
				else if (map[i][j] == '_' && (map[i][j - 1] != '1' || map[i][j + 1] != '1'))
					return (ft_set_error_static(MAP_DOORS_NOT_BETWEEN_WALLS, error, VALIDATOR));
			}
		}
	}
}

void	ft_check_every_cell(char **map, t_error *error)
{
	int	i;
	int	j;

	if (ft_has_error(error))
		return ;
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
