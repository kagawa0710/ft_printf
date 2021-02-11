/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:42:02 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/06 11:12:15 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// %% -> %を出力
int		write_percent(t_fmt *fmt_data)
{
	int		width;

	width = 0;

	// widthがある場合埋める文字数を取っておく
	if (fmt_data->width > 0)
		width = fmt_data->width - 1;

	// 左詰めフラグの場合は先に出力
	if (fmt_data->flag & FLAG_LEFT)
	{
		write(1, "%", 1);
		write_times(' ', width);
	}
	else
	{
		// 0埋めか空白埋めかを判断し投げる widthが0なら何もしない。
		if (fmt_data->flag & FLAG_ZEROS)
			write_times('0', width);
		else
			write_times(' ', width);
		write(1, "%", 1);
	}
	return (width + 1);
}
