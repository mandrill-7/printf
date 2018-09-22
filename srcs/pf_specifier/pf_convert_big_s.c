/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_big_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:15:06 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:18:06 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int64_t			pf_wchar_tlen(wchar_t *w)
{
	int64_t		len;

	len = 0;
	while (*w)
	{
		if (IS_DEMI_CODETS(*w) || *w < 0)
			return (-1);
		if ((*w < EIGHT_BITS_MIN_VALUE) ||
				(*w <= BYTE_MAX_VALUE && MB_CUR_MAX == 1))
			len += 1;
		else if (*w < TWELVE_BITS_MIN_VALUE && MB_CUR_MAX > 1)
			len += 2;
		else if (*w < SEVENTEEN_BITS_MIN_VALUE && MB_CUR_MAX > 2)
			len += 3;
		else if (*w < TWENTYTWO_BITS_MIN_VALUE && MB_CUR_MAX > 3)
			len += 4;
		else
			return (-1);
		++w;
	}
	return (len);
}

int64_t			pf_wchar_tnlen(wchar_t *w, int precision)
{
	int64_t		len;

	len = 0;
	while (*w && precision)
	{
		if (IS_DEMI_CODETS(*w) || *w < 0)
			return (-1);
		if ((*w < EIGHT_BITS_MIN_VALUE) ||
				(*w <= BYTE_MAX_VALUE && MB_CUR_MAX == 1))
		{
			--precision;
			++len;
		}
		else if (*w < TWELVE_BITS_MIN_VALUE && MB_CUR_MAX > 1)
			((precision -= 2) < 0) ? (precision = 0) : (len += 2);
		else if (*w < SEVENTEEN_BITS_MIN_VALUE && MB_CUR_MAX > 2)
			((precision -= 3) < 0) ? (precision = 0) : (len += 3);
		else if (*w < TWENTYTWO_BITS_MIN_VALUE && MB_CUR_MAX > 3)
			((precision -= 4) < 0) ? (precision = 0) : (len += 4);
		else
			return (-1);
		++w;
	}
	return (len);
}

void			pf_insert_wchar(t_env *env, wchar_t *w, size_t len)
{
	while (len)
	{
		if ((*w < EIGHT_BITS_MIN_VALUE) ||
				(*w <= BYTE_MAX_VALUE && MB_CUR_MAX == 1))
		{
			pf_set_char(env, *w);
			len -= 1;
		}
		else if (*w < TWELVE_BITS_MIN_VALUE)
		{
			pf_handle_two_bytes(env, *w);
			len -= 2;
		}
		else if (*w < SEVENTEEN_BITS_MIN_VALUE)
		{
			pf_handle_three_bytes(env, *w);
			len -= 3;
		}
		else if (*w < TWENTYTWO_BITS_MIN_VALUE)
		{
			pf_handle_four_bytes(env, *w);
			len -= 4;
		}
		++w;
	}
}

static void		pf_fill_conv(t_env *env, t_attr *attr, const wchar_t *string, \
		int64_t string_len)
{
	if (attr->flags & F_MINUS)
	{
		pf_insert_wchar(env, (wchar_t *)string, string_len);
		if ((int64_t)attr->width > string_len)
			pf_set_static_memory(env, ' ', attr->width - string_len);
	}
	else
	{
		if ((int64_t)attr->width > string_len)
			pf_set_static_memory(env, ' ', attr->width - string_len);
		pf_insert_wchar(env, (wchar_t *)string, string_len);
	}
}

bool			pf_convert_big_s(t_env *env, t_attr *attr, \
		const wchar_t *string)
{
	int64_t		string_len;

	if (attr->precision == -1)
	{
		if ((string_len = pf_wchar_tlen((wchar_t *)string)) == -1)
			return (PF_ERROR);
	}
	else
	{
		if ((string_len = pf_wchar_tnlen((wchar_t *)string,
						attr->precision)) == -1)
			return (PF_ERROR);
	}
	pf_fill_conv(env, attr, string, string_len);
	return (0);
}
