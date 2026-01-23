/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 20:47:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include <unistd.h> //NULL
#include "libft.h" //ft_calloc
#include "errorctx.h" //ft_set_error

t_data	*ft_init_data(t_error *error)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, (sizeof(t_data)));
	if (!data)
		return (ft_set_error_system(error), NULL);
	return (data);
}
