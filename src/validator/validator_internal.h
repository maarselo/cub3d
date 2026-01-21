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

# include "errorctx.h" //struct

void	ft_check_argument(int argc, char *file, t_error *error);
void	ft_check_config(char *file, t_error *error);
void	ft_check_map(char *file, t_error *error);

#endif