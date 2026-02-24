/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 19:26:48 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MLX42.h"
# include "cub3d.h"
# include "game.h"

typedef enum s_start_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_start_orientation;

//Colors
typedef struct s_colors
{
	uint32_t	floor;
	uint32_t	ceiling;
}	t_colors;

//Textures
typedef struct s_weapon
{
	mlx_image_t	*idle;
	mlx_image_t	*shoot;
	mlx_image_t	*smoke;
	bool		is_shooting;
}	t_weapon;
typedef struct textures
{
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	mlx_image_t	*door;
	mlx_image_t	*timer;
	mlx_image_t	*date;
	t_weapon	*weapon;
}	t_textures;

//Map
typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
}	t_map;

//Enemies
typedef struct s_enemy
{
	double			pos_x;
	double			pos_y;
	bool			is_died;
	unsigned short	frame;
	struct s_enemy	*next;
}	t_enemy;
typedef struct s_enemies
{
	int			total_enemies;
	mlx_image_t	*enemy_frame1;
	mlx_image_t	*enemy_frame2;
	t_enemy	*enemies;
}	t_enemies;

//Player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

//Game
typedef struct s_mlx
{
	mlx_t			*window;
	mlx_image_t		*framebuffer;
	double			z_buffer[WINDOW_WIDTH];
}	t_mlx;

//Bonus
//Minimap
typedef struct s_minimap
{
	int	start_x;
	int	start_y;
	int	final_x;
	int	final_y;
	int	center_x;
	int	center_y;
	int	tile_size;
}	t_minimap;

//parser.c
void	ft_parser(char *file, t_data *data, t_error *error);

//init_data.c
t_data	*ft_init_data(t_error *error);

#endif