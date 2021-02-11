/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:42:10 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/06 11:12:02 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

// 出力変換指定子確認のため初期化
void		initialize_t_fmt(t_fmt *fmt_data)
{
	// フラグ
	fmt_data->flag = FLAG_NONE;

	// 精度
	fmt_data->precision = -1;

	// 長さ修飾子(今回は対応していない)
	fmt_data->modifier = LEN_NONE;

	// 変換指定子
	fmt_data->type = TYPE_NONE;

	// 最小フィールド幅
	fmt_data->width = 0;

	// 桁数
	fmt_data->digit = 0;

	// マイナスフラグ
	fmt_data->is_minus = 0;

	// 出力する数字が0か判断
	fmt_data->is_zero = 0;
}

bool		is_unsigned_type(enum e_type type)
{
	return (type == TYPE_UINT || type == TYPE_HEX_UP ||
			type == TYPE_HEX_LOW || type == TYPE_POINTER);
}

bool		is_integer_type(enum e_type type)
{
	return (type == TYPE_INT || type == TYPE_UINT ||
			type == TYPE_HEX_LOW || type == TYPE_HEX_UP);
}

bool		will_output_base(t_fmt *fmt_data)
{
	return (fmt_data->type == TYPE_POINTER ||
		((fmt_data->type == TYPE_HEX_UP || fmt_data->type == TYPE_HEX_LOW) &&
		fmt_data->flag & FLAG_BASE && !fmt_data->is_zero));
}

uint64_t	get_base_from_type(enum e_type type)
{
	if (type == TYPE_HEX_LOW || type == TYPE_HEX_UP || type == TYPE_POINTER)
		return (16);
	else
		return (10);
}
