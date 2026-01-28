/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:08:20 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h" //t_data struct
# include "MLX42.h"

mlx_image_t	*ft_texture_to_img(t_data *data, char *texture_str);
void		ft_init_textures(char *file, t_data *data);
void		ft_init_player(t_data *data);
void		ft_init_map(char *file, t_data *data);
void		ft_init_mlx(t_data *data);

#endif