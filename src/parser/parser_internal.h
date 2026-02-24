/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 16:42:00 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h" //t_data struct
# include "MLX42.h"

void		ft_init_colors(char *file, t_data *data);
void		ft_init_map(char *file, t_data *data);
void		ft_init_enemies(t_data *data);
void		ft_init_player(t_data *data);
void		ft_init_mlx(t_data *data);
void		ft_init_textures(char *file, t_data *data);
void		ft_init_minimap(t_data *data);

#endif