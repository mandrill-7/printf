/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:18:39 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:18:40 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_handle_overload(t_attr *attr, int64_t *n, \
		char *ext_signed_char)
{
	if (*n < 0)
	{
		*n *= -1;
		*ext_signed_char = '-';
	}
	else if (attr->flags & F_PLUS)
		*ext_signed_char = '+';
	else if (attr->flags & F_SPACE)
		*ext_signed_char = ' ';
	else
		*ext_signed_char = 0;
	if (attr->flags & F_MINUS)
		attr->flags &= ~(F_ZERO);
	if (attr->flags & F_ZERO && attr->precision == -1)
	{
		attr->precision = attr->width - (*ext_signed_char != 0);
		attr->width = 0;
	}
}

static void		pf_set_dbuff(char dbuffer[25], t_dbuff_set *set, t_attr *attr, \
		int64_t n)
{
	if (n != 0 || attr->precision != 0)
	{
		if (attr->flags & F_QUOTE && MB_CUR_MAX == 4)
			set->s = pf_rev_itoa_base_quote(&dbuffer[24], n, 10, 3);
		else
			set->s = pf_rev_itoa_base(&dbuffer[24], n, 10);
		set->len = &dbuffer[24] - set->s + 1;
	}
	else
		set->len = 0;
	if (attr->precision > set->len)
		attr->precision -= set->len;
	else
		attr->precision = 0;
}

static void		pf_fill_conv(t_env *env, t_attr *attr, const t_dbuff_set *set, \
		char ext_signed_char)
{
	if (attr->flags & F_MINUS)
	{
		if (ext_signed_char != 0)
			pf_set_char(env, ext_signed_char);
		pf_set_static_memory(env, '0', attr->precision);
		pf_set_dynamic_memory(env, set->s, set->len);
		if (attr->width > set->width_len)
			pf_set_static_memory(env, ' ', attr->width - set->width_len);
	}
	else
	{
		if (attr->width > set->width_len)
			pf_set_static_memory(env, ' ', attr->width - set->width_len);
		if (ext_signed_char != 0)
			pf_set_char(env, ext_signed_char);
		pf_set_static_memory(env, '0', attr->precision);
		pf_set_dynamic_memory(env, set->s, set->len);
	}
}

bool			pf_convert_d(t_env *env, t_attr *attr)
{
	int64_t			n;
	char			ext_signed_char;
	char			dbuffer[25];
	t_dbuff_set		set;

	if (attr->spec != 'D')
		n = pf_cast_svalue(&env->arg_list, attr->lenght_mod);
	else
		n = PF_GET_NEXT_ARG(env->arg_list, long);
	pf_handle_overload(attr, &n, &ext_signed_char);
	pf_set_dbuff(dbuffer, &set, attr, n);
	set.width_len = attr->precision + set.len + (ext_signed_char != 0);
	pf_fill_conv(env, attr, &set, ext_signed_char);
	return (0);
}
