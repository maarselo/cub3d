/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 16:30:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_colors		t_colors;
typedef struct textures		t_textures;
typedef struct s_map		t_map;
typedef struct s_enemies	t_enemies;
typedef struct s_player		t_player;
typedef struct s_mlx		t_mlx;

typedef struct s_error		t_error;

typedef struct s_minimap	t_minimap;

typedef struct s_data
{
	t_colors	*colors;
	t_textures	*textures;
	t_map		*map;
	t_player	*player;
	t_mlx		*mlx;
	
	t_enemies	*enemies;
	t_minimap	*minimap;
	t_error		*error;
}	t_data;

#endif