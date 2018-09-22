/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_big_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:14:47 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:57 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void (*g_handle_byte[4])(t_env *, wint_t) =
{
	pf_handle_one_byte,
	pf_handle_two_bytes,
	pf_handle_three_bytes,
	pf_handle_four_bytes
};

int64_t		pf_wint_tlen(wint_t c)
{
	if (IS_DEMI_CODETS(c) || c < 0)
		return (-1);
	if ((c < EIGHT_BITS_MIN_VALUE) || (c <= BYTE_MAX_VALUE && MB_CUR_MAX == 1))
		return (1);
	else if (c < TWELVE_BITS_MIN_VALUE && MB_CUR_MAX > 1)
		return (2);
	else if (c < SEVENTEEN_BITS_MIN_VALUE && MB_CUR_MAX > 2)
		return (3);
	else if (c < TWENTYTWO_BITS_MIN_VALUE && MB_CUR_MAX > 3)
		return (4);
	else
		return (-1);
}

bool		pf_convert_big_c(t_env *env, t_attr *attr, wint_t c)
{
	int64_t		len;

	if ((len = pf_wint_tlen(c)) == -1)
		return (PF_ERROR);
	if (attr->flags & F_MINUS)
	{
		g_handle_byte[len - 1](env, c);
		if ((int64_t)attr->width > len)
			pf_set_static_memory(env, ' ', attr->width - len);
	}
	else
	{
		if ((int64_t)attr->width > len)
			pf_set_static_memory(env, ' ', attr->width - len);
		g_handle_byte[len - 1](env, c);
	}
	return (0);
}
