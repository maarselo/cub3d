/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 13:59:21 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "cub3d.h"

//free_cile_content
void	ft_free_file_content(char **content);

//free_content_assigned.c
void	ft_free_content_assigned(int i, char **file_content);

//free_split.c
void	ft_free_split(char **split);


//free_data.c
void	ft_free_data(t_data *data);
#endif