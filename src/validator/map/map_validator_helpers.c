/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "libft.h" //ft_stlen

int	ft_get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_get_map_width(char **map)
{
	int j;

	j = 0;
	while (map[0][j])
		j++;
	return (j);
}

void	ft_check_space_side(int row, int col, char **map, t_error *error)
{
	if (ft_has_error(error))
		return ;
	else if (row < 0 || row >= ft_get_map_height(map) ||
		col < 0 || col >= ft_get_map_width(map))
		return ;
	else if (map[row][col] == '_' || map[row][col] == '|')
		return ft_set_error_static(MAP_DOORS_OUTSIDE_WALLS, error, VALIDATOR);
	else if (map[row][col] == 'e')
		return (ft_set_error_static(MAP_ENEMIES_OUTSIDE_WALLS, error, VALIDATOR));
}

void	ft_check_cell(int row, int col, char **map, t_error *error)
{
	if (ft_has_error(error))
		return ;
	if (row < 0 || row >= ft_get_map_height(map))
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
	if (col < 0 || col >= ft_get_map_width(map))
		return (ft_set_error_static(MAP_NOT_CLOSED, error, VALIDATOR));
	if (map[row][col] == '-')
		return (ft_set_error_static(MAP_SPACE_NEXTTO_FLOOR, error, VALIDATOR));
}
