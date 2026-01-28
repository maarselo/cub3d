/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:21:22 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //enum vars
#include "libft.h" // put messages
#include "free.h"

bool	ft_has_error(t_error *error)
{
	return (error->error_number != ERROR_NONE);
}

bool	ft_error_handler(t_error *error, t_data *data)
{
	if (!ft_has_error(error))
		return (false);
	ft_putendl_fd("Error\033[1;31m", 2);
	ft_putendl_fd(error->message, 2);
	ft_putstr_fd("\033[0m", 2);
	if (error->is_freeable)
		free(error->message);
	free(error);
	error = NULL;
	if (data)
		ft_free_data(data);
	return (true);
}
