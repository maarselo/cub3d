/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:05:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" //struct in parser
#include "cub3d.h" //t_data struct
#include "errorctx.h" //error struct
#include "libft.h" //ft_calloc

#define PATH_ENEMY1 "./textures/enemies/enemy1.png"
#define PATH_ENEMY2 "./textures/enemies/enemy2.png"

mlx_image_t	*ft_texture_to_img(char *texture_path, t_data *data);

static int	ft_count_enemies(t_data *data)
{
	int	i;
	int	j;
	int	total_enemies;

	i = -1;
	total_enemies = 0;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
			if (data->map->map[i][j] == 'e')
				total_enemies++;
	}
	return (total_enemies);
}

static t_enemy	*ft_init_enemy(int row, int col)
{
	t_enemy	*enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->pos_y = (double)row + 0.5;
	enemy->pos_x = (double)col + 0.5;
	enemy->frame = 1;
	return (enemy);
}

static void	ft_enemy_handler(int row, int col, t_data *data)
{
	static t_enemy	*last_enemy;
	t_enemy			*current_enemy;

	current_enemy = ft_init_enemy(row, col);
	if (!current_enemy)
		return (ft_set_error_system(data->error));
	if (!data->enemies->enemies)
		data->enemies->enemies = current_enemy;
	else
		last_enemy->next = current_enemy;
	last_enemy = current_enemy;
}

static void	ft_init_enemies_texture(t_data *data)
{
	data->enemies->enemy_frame1 = ft_texture_to_img(PATH_ENEMY1, data);
	if (ft_has_error(data->error))
		return ;
	data->enemies->enemy_frame2 = ft_texture_to_img(PATH_ENEMY2, data);
}

void	ft_init_enemies(t_data *data)
{
	int		row;
	int		col;

	if (ft_has_error(data->error))
		return ;
	data->enemies->total_enemies = ft_count_enemies(data);
	if (data->enemies->total_enemies == 0)
	{
		data->enemies->enemies = NULL;
		return ;
	}
	row = -1;
	while (data->map->map[++row])
	{
		col = -1;
		while (data->map->map[row][++col])
		{
			if (data->map->map[row][col] == 'e')
				ft_enemy_handler(row, col, data);
			if (ft_has_error(data->error))
				return ;
		}
	}
	ft_init_enemies_texture(data);
}
