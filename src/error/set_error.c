/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "libft.h" //ft_multijoin

void	ft_set_error_static(int errnum, t_error *error, int process)
{
	error->error_number = errnum;
	error->message = ft_strerror(errnum, process);
	error->is_freeable = false;
}

void	ft_set_error_join(int errnum, char *join, t_error *error, int process)
{
	error->error_number = errnum;
	error->message = ft_multijoin(4, ft_strerror(errnum, process),
			" \"", join, "\".");
	error->is_freeable = true;
}
