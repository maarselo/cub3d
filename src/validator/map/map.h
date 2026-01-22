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

char	**ft_get_map(char *file, t_error *error);
void	ft_fill_spaces(char **map, t_error *error);
int		ft_get_map_height(char **map);
char	*ft_replace_spaces(int chars, char *str, t_error *error);
int		ft_get_map_last_idx(int start_idx, char **content);
int		ft_get_map_start_idx(char **content);
#endif