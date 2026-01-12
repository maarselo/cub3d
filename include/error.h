/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h> //struct variable

typedef enum	e_process
{
	SYSTEM,
	VALIDATOR,

}	t_process;

typedef struct	s_error
{
	int		error_number;
	char	*message;
	bool	is_freeable;
}	t_error;


//validator errors
typedef enum	e_validator_error
{
	ERROR_NONE,
	
	ARGUMENTS_NUMBER,
	MAP_EXTENSION,
	
	ERROR_COUNT
}	t_validator_error;



//init_error.c
t_error	*ft_init_error(void);

#endif