/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATOR_H
# define MAP_VALIDATOR_H

#include "errorctx.h" //struct

void	ft_check_cell(int i, int j, char **map, t_error *error);

#endif