/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:41:49 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/05 16:46:14 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

// %c 引数を文字として出力
int		write_char(t_fmt *fmt_data, va_list *ap)
{
	// widthによって空白を出力
	// flag
	unsigned char	c;
	int				write_size;

	write_size = 0;
	c = (unsigned char)va_arg(*ap, int);
	if (fmt_data->width > 0 && !(fmt_data->flag & FLAG_LEFT))
		write_size += write_times(' ', fmt_data->width - 1);
	write_size += write(1, &c, 1);
	if (fmt_data->width > 0 && fmt_data->flag & FLAG_LEFT)
		write_size += write_times(' ', fmt_data->width - 1);
	return (write_size);
}

// %s 引数を文字列として出力
int		write_string(t_fmt *fmt_data, va_list *ap)
{
	const char	*str;
	long long	output_str_len;
	long long	width;

	str = va_arg(*ap, const char *);

	// 文字列がなければ"(null)"を出力
	str = str ? str : "(null)";
	// 文字列の長さを計算
	output_str_len = ft_strlen(str);
	width = 0;

	// 文字列の長さよりprecisionが小さければprecisionを優先
	if (fmt_data->precision >= 0 && output_str_len > fmt_data->precision)
		output_str_len = fmt_data->precision;

	// widthより文字列の長さが小さければ空白などを出力用に準備
	if (fmt_data->width > output_str_len)
		width = fmt_data->width - output_str_len;

	// widthと埋めるものに注意しながら空白を出力
	if (!(fmt_data->flag & FLAG_LEFT))
		write_times(fmt_data->flag & FLAG_ZEROS ? '0' : ' ', width);
	write(1, str, output_str_len);
	if (fmt_data->flag & FLAG_LEFT)
		write_times(' ', width);
	return (width + output_str_len);
}
