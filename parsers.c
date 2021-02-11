/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:41:06 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/05 17:09:36 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

// 理論和で組み合わせを簡潔に表現する。
//  |= 理論和(or)
// &= 理論積
// ~　否定(数字を逆転)

// フラグチェック
void	parse_flag(const char **format, t_fmt *fmt_data)
{
	// 先頭から見ていって今見ているものがフラグの指定子に当てはまるか確認。
	while (**format && (**format == '0' || **format == '-' ||
						**format == '#' || **format == '+' ||
						**format == ' '))
	{
		if (**format == '0')
			fmt_data->flag |= FLAG_ZEROS;
		if (**format == '-')
			fmt_data->flag |= FLAG_LEFT;
		if (**format == '#')
			fmt_data->flag |= FLAG_BASE;
		if (**format == '+')
			fmt_data->flag |= FLAG_SIGN;
		if (**format == ' ')
			fmt_data->flag |= FLAG_SPACE;
		(*format)++;
	}
	// 左詰めと0埋めが同時に指示されてる -> 左埋め('-')を採用
	if (fmt_data->flag & FLAG_LEFT && fmt_data->flag & FLAG_ZEROS)
		fmt_data->flag &= ~FLAG_ZEROS;
	// '+'と' 'が同時に指示されてる -> '+'を採用(正の数の場合+を表示)
	if (fmt_data->flag & FLAG_SIGN && fmt_data->flag & FLAG_SPACE)
		fmt_data->flag &= ~FLAG_SPACE;
}

void	parse_width(const char **format, t_fmt *fmt_data, va_list *ap)
{
	int width;

	// '*'だったら引数で渡された値を width として使用する
	if (**format == '*')
	{
		width = va_arg(*ap, int);
		if (width < 0)
		{
			// 引数が負の数の場合　flagで'-'を採用
			fmt_data->flag |= FLAG_LEFT;
			fmt_data->flag &= ~FLAG_ZEROS;
			width = -width;
		}
		// widthに格納
		fmt_data->width = width;
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		// formatから数字を取得->atoiで文字列として格納
		width = ft_atoi(*format);
		fmt_data->width = width;
		(*format) += num_len(*format);
	}
}

// 精度がマイナスは不適とみる
void	parse_precision(const char **format, t_fmt *fmt_data, va_list *ap)
{
	long long precision;

	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			precision = va_arg(*ap, int);
			// 正の場合のみ
			if (precision >= 0)
				// 精度に格納
				fmt_data->precision = precision;
			(*format)++;
		}
		else if (**format == '-')
		{
			// 次の文字へ
			(*format)++;
			(*format) += num_len(*format);
		}
		else
		{
			// 数字を文字列として格納
			fmt_data->precision = ft_atoi(*format);
			(*format) += num_len(*format);
		}
	}
}

void	parse_type(const char **format, t_fmt *fmt_data)
{
	if (**format == 'd' || **format == 'i')
		// int 値を符号付き 10 進数として出力
		fmt_data->type = TYPE_INT;

	else if (**format == 'u')
		// int 値を符号なし 10 進数として出力します
		fmt_data->type = TYPE_UINT;

	else if (**format == 'x')
		// 	int 値を符号なし 16 進数として出力します。10 ～ 15 の桁は 'a' ～'f' で表されます。
		fmt_data->type = TYPE_HEX_LOW;

	else if (**format == 'X')
		// int 値を符号なし 16 進数として出力します。10 ～ 15 の桁は 'A' ～'F' で表されます。
		fmt_data->type = TYPE_HEX_UP;

	else if (**format == 'c')
		// int 値を文字として出力します
		fmt_data->type = TYPE_CHAR;

	else if (**format == 's')
		// 文字列を出力します。
		fmt_data->type = TYPE_STRING;

	else if (**format == 'p')
		// ポインタの値を 16 進数で出力します。
		fmt_data->type = TYPE_POINTER;

	else if (**format == '%')
		// %を出力します
		fmt_data->type = TYPE_PERCENT;

	else
		return ;

	// 数字系の出力
	if (is_integer_type(fmt_data->type))
		// 精度(precision)が指定されている場合は精度を優先
		if (fmt_data->precision != -1)
			fmt_data->flag &= ~FLAG_ZEROS;
	if (is_integer_type(fmt_data->type) || fmt_data->type == TYPE_POINTER)
		// 精度(precision)が指定されている場合は1にする(数字系の出力フラグとして利用)
		if (fmt_data->precision == -1)
			fmt_data->precision = 1;
	(*format)++;
}
