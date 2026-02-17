/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 21:28:19 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "errorctx.h"

//map_validator.c
void	ft_detect_invalid_chars(char **map, t_error *error);
int		ft_get_map_height(char **map);
void	ft_check_cell(int i, int j, char **map, t_error *error);
void	ft_check_doors(char **map, t_error *error);
void	ft_check_every_cell(char **map, t_error *error);

//map_content.c
char	**ft_get_map(char *file, t_error *error);
void	ft_fill_spaces(char **map, t_error *error);
#endif