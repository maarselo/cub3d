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
#include "free.h" //ft_free_file

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
