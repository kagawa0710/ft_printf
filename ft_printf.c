/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:42:27 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/06 11:28:40 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_printf(const char *format, ...)
{
	int		write_size;
	va_list	ap;

	write_size = 0;

	// 可変長の関数
	va_start(ap, format);

	while (*format)
	{
		// %があれば指定子を確認して引数をうまいこと出力
		if (*format == '%')
		{
			format++;

			// 対応する引数とともに長旅へ
			write_size += parse_and_write(&format, &ap);
		}

		// %がなければそのまま文字列として出力
		else
		{
			write_size += write(1, format, 1);
			format++;
		}
	}

	// 礼儀
	va_end(ap);

	// 出力した長さを返す
	return (write_size);
}

int		parse_and_write(const char **format, va_list *ap)
{
	t_fmt	fmt_data;

	// 初期化
	initialize_t_fmt(&fmt_data);

	// フラグを確認
	parse_flag(format, &fmt_data);

	// widthを確認
	parse_width(format, &fmt_data, ap);

	// 精度を確認
	parse_precision(format, &fmt_data, ap);

	// 変換指定子を確認
	parse_type(format, &fmt_data);

	// いざ出力(出力した文字数をreturn)
	return (write_fmt_data(&fmt_data, ap));
}

int		write_fmt_data(t_fmt *fmt_data, va_list *ap)
{
	long long	n;

	// %%
	if (fmt_data->type == TYPE_PERCENT)
		return (write_percent(fmt_data));

	// %c
	if (fmt_data->type == TYPE_CHAR)
		return (write_char(fmt_data, ap));

	// %s
	else if (fmt_data->type == TYPE_STRING)
		return (write_string(fmt_data, ap));

	// 数字系
	else if (fmt_data->type == TYPE_UINT || fmt_data->type == TYPE_HEX_LOW ||
			fmt_data->type == TYPE_HEX_UP || fmt_data->type == TYPE_INT)
	{
		// unsignedは絶対値で受ける
		n = fmt_va_arg(fmt_data, ap);
		return (write_integer(fmt_data, n));
	}
	// ポインタ
	else if (fmt_data->type == TYPE_POINTER)
	{
		n = va_arg(*ap, long);
		return (write_integer(fmt_data, n));
	}
	return (0);
}
