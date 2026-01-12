/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //enum_valor && ft_set_error* && struct
#include "validator_internal.h" //EXTENSION_FILE
#include "libft.h" //ft_str*

static void	ft_check_arguments_number(int argc, t_error *error)
{
	if (ft_has_error(error))
		return ;
	if (argc != 2)
		return (ft_set_error_static(ARGUMENTS_NUMBER, error, VALIDATOR));
}

static void	ft_check_file_len(char *argv, t_error *error)
{
	if (ft_has_error(error))
		return ;
	if (!ft_strlen(argv))
		return (ft_set_error_static(EMPTY_ARGUMENT, error, VALIDATOR));
}

static void	ft_check_extension_file(char *argv, t_error *error)
{
	char	*point_found;

	if (ft_has_error(error))
		return ;
	point_found = ft_strrchr(argv, '.');
	if (!point_found)
		return (ft_set_error_join(MAP_EXTENSION, argv, error, VALIDATOR));
	if (ft_strncmp(EXTENSION_CUB, argv + (point_found - argv), ft_strlen(argv)))
		return (ft_set_error_join(MAP_EXTENSION, argv, error, VALIDATOR));
}

void	ft_check_argument(int argc, char **argv, t_error *error)
{
	ft_check_arguments_number(argc, error);
	ft_check_file_len(argv[1], error);
	ft_check_extension_file(argv[1], error);
}
