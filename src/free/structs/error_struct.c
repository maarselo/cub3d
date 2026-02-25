/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_struct.c                                       :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h"//t_map
#include "errorctx.h" //free_terror
#include <stdlib.h> //free()

void	ft_free_error_struct(t_data *data)
{
	if (data->error->is_freeable)
		free(data->error->message);
	free(data->error);
	data->error = NULL;
}
