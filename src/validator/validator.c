/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 21:18:56 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	ft_validator(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Invalid.", 2));
}