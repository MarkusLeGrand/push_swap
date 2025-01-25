/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkantzer <lkantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:39:49 by lkantzer          #+#    #+#             */
/*   Updated: 2025/01/25 23:39:50 by lkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_handle_char(va_list ap);
int		ft_handle_string(va_list ap);
int		ft_handle_int(va_list ap);
int		ft_handle_unsigned(va_list ap);
int		ft_handle_pointer(va_list ap);
int		ft_handle_hexlower(va_list ap);
int		ft_handle_hexupper(va_list ap);
int		ft_handle_percent(void);
int		ft_putchar(char c);
int		ft_putnbr_base(unsigned long long nb, const char *base);

#endif