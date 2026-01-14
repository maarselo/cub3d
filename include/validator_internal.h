/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 13:59:21 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_INTERNAL_H
# define VALIDATOR_INTERNAL_H	

# define EXTENSION_CUB ".cub"

# define NORTH_TEX "NO "
# define SOUTH_TEX "SO "
# define WEST_TEX "WE "
# define EAST_TEX "EA "
# define FLOOR_COLOR "F "
# define CEILING_COLOR "C "

# include "errorctx.h" //use in prototype function

typedef struct s_config_flags
{
	bool	no_found;
	bool	so_found;
	bool	we_found;
	bool	ea_found;
	bool	f_found;
	bool	c_found;
} t_config_flags;

void	ft_check_argument(int argc, char *file, t_error *error);
void	ft_check_map(char *file, t_error *error);

#endif