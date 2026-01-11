/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:21:17 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdlib.h>
#include <stdio.h>

t_error	*ft_init_error(void)
{
	t_error	*error;

	error = (t_error *)malloc(sizeof(t_error));
	if  (!error)
		return (perror("cub3d"), exit(1), NULL);
	error->error_number = ERROR_NONE;
	error->message = NULL;
	error->is_freeable = false;
	return (error);
}
