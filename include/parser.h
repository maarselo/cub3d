/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/07 21:06:56 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MLX42.h"
# include "cub3d.h"

typedef enum s_start_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
} t_start_orientation;

//Colors
typedef struct s_colors
{
	uint32_t	floor;
	uint32_t	ceiling;
} t_colors;


//Textures
typedef struct s_weapon
{
	mlx_image_t	*idle;
	mlx_image_t	*reload;
	mlx_image_t	*aim;
	mlx_image_t	*shoot;
} t_weapon;
typedef struct textures
{
	mlx_image_t	*north;
	mlx_image_t *south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	mlx_image_t	*door;
	mlx_image_t	*timer;
	mlx_image_t *date;
	t_weapon	*weapon;
} t_textures;


//Map
typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
} t_map;


//Enemies
typedef struct s_enemy
{
	double			pos_x;
	double			pos_y;
	struct s_enemy	*next;
} t_enemy;
typedef struct s_enemies
{
	int		total_enemies;
	t_enemy	*enemies;
} t_enemies;


//Player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;


//Game
typedef struct s_mlx
{
	unsigned int	width;
	unsigned int	height;
	mlx_t			*window;
	mlx_image_t		*framebuffer;
} t_mlx;



//parser.c
void	ft_parser(char *file, t_data *data, t_error *error);

//init_data.c
t_data	*ft_init_data(t_error *error);

#endif