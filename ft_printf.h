/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:42:33 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/05 16:45:56 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include <wchar.h>

enum			e_flag
{
	// フラグ
	// 2 進リテラル
	FLAG_NONE = 0b00000,//-> 0
	FLAG_LEFT = 0b00001,//-> 1
	FLAG_SIGN = 0b00010,//-> 2
	FLAG_SPACE = 0b00100,//-> 3
	FLAG_BASE = 0b01000,//-> 4
	FLAG_ZEROS = 0b10000//-> 5
};

enum	e_len
{
	LEN_NONE = 0,
	LEN_L = 1,
	LEN_LL = 2,
	LEN_H = 3,
	LEN_HH = 4,
};

enum			e_type
{
	TYPE_NONE = 0,
	TYPE_PERCENT = 1,
	TYPE_INT = 2,
	TYPE_UINT = 3,
	TYPE_CHAR = 4,
	TYPE_STRING = 5,
	TYPE_POINTER = 6,
	TYPE_HEX_LOW = 7,
	TYPE_HEX_UP = 8,
};

typedef struct	s_fmt
{
	enum e_flag	flag;
	long long	width;
	long long	precision;
	enum e_len	modifier;
	enum e_type type;
	long long	is_minus;
	long long	is_zero;
	long long	digit;
}				t_fmt;

int				ft_printf(const char *format, ...);
int				parse_and_write(const char **format, va_list *ap);
void			parse_flag(const char **format, t_fmt *fmt_data);
void			parse_width(const char **format, t_fmt *fmt_data, va_list *ap);
void			parse_precision(const char **format,
					t_fmt *fmt_data, va_list *ap);
void			parse_modifier(const char **format, t_fmt *fmt_data);
void			parse_type(const char **format, t_fmt *fmt_data);
int				write_fmt_data(t_fmt *fmt_data, va_list *ap);
int				write_char(t_fmt *fmt_data, va_list *ap);
int				write_wchr(t_fmt *fmt_data, va_list *ap);
int				write_string(t_fmt *fmt_data, va_list *ap);
int				write_wstr(t_fmt *fmt_data, va_list *ap);
int				write_integer(t_fmt *fmt_data, long long n);
int				write_percent(t_fmt *fmt_data);
void			initialize_t_fmt(t_fmt *fmt_data);
long long		fmt_va_arg(t_fmt *fmt_data, va_list *ap);
bool			is_unsigned_type(enum e_type type);
bool			is_integer_type(enum e_type type);
bool			will_output_base(t_fmt *fmt_data);
bool			will_output_sign(t_fmt *fmt_data);
char			*get_sign_prefix(t_fmt *fmt_data);
uint64_t		get_base_from_type(enum e_type type);
int				write_times(char c, int n);
size_t			ft_wcslen (wchar_t *s);
int				fmt_itoa(long long n, t_fmt *fmt_data,
						char **num, long long len);
int				output_fmt_nbr(char *num, t_fmt *fmt_data,
						int prefix_size);
int				write_fmt_nbr(char *num, t_fmt *fmt_data,
						int spaces, int zeros);

#endif
