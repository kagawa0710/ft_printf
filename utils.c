/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykagawa <ykagawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 02:41:18 by ykagawa           #+#    #+#             */
/*   Updated: 2021/02/05 16:29:22 by ykagawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"


// cをn回出力
int		write_times(char c, int n)
{
	int i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i++ < n)
		write(1, &c, 1);
	return (n);
}

size_t	ft_wcslen(wchar_t *s)
{
	size_t	len;

	len = 0;
	while (s[len] != L'\0')
	{
		if (s[++len] == L'\0')
			return (len);
		if (s[++len] == L'\0')
			return (len);
		if (s[++len] == L'\0')
			return (len);
		len++;
	}
	return (len);
}
