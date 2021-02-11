/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:42:16 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/06 11:38:35 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool		will_output_sign(t_fmt *fmt_data)
{
	return (fmt_data->is_minus ||
		((fmt_data->flag & FLAG_SIGN || fmt_data->flag & FLAG_SPACE) &&
			!is_unsigned_type(fmt_data->type)));
}

char		*get_sign_prefix(t_fmt *fmt_data)
{
	if (fmt_data->is_minus)
		return ("-");
	else if (fmt_data->flag & FLAG_SPACE)
		return (" ");
	else if (fmt_data->flag & FLAG_SIGN)
		return ("+");
	else
		return ("");
}

long long	fmt_va_arg(t_fmt *fmt_data, va_list *ap)
{
	long long	n;

	if (is_unsigned_type(fmt_data->type))
		n = (unsigned int)va_arg(*ap, int);
	else
		n = va_arg(*ap, int);
	return (n);
}
