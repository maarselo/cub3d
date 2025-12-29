/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:21:59 by mvillavi          #+#    #+#             */
/*   Updated: 2025/12/29 15:22:07 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

void	ft_putchar_pf(char c, int *count);
void	ft_putstr_pf(char *s, int *count);
void	ft_putnbr_base_pf(long num, char *base, int *count);
void	ft_putnbr_ulbase_pf(unsigned long num, char *base, int *count);
void	ft_putptr_pf(void *num, int *count);

#endif