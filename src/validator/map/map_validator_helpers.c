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

static int	ft_get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_check_cell(int i, int j, char **map, t_error *error)
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
