/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:14:39 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:52 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_handle_overload(t_attr *attr)
{
	if (attr->flags & F_MINUS)
		attr->flags &= ~(F_ZERO);
	if (attr->flags & F_ZERO && attr->precision == -1)
	{
		attr->precision = attr->width;
		attr->width = 0;
		if (attr->flags & F_SHARP)
			attr->precision -= 2;
	}
}

static void		pf_set_dbuff(char dbuffer[79], t_dbuff_set *set, t_attr *attr, \
		uint64_t n)
{
	if (n != 0 || attr->precision != 0 || attr->flags & F_SHARP)
	{
		if (attr->flags & F_QUOTE && MB_CUR_MAX == 4)
			set->s = pf_rev_itoa_base_quote(&dbuffer[78], n, 2, 4);
		else
			set->s = pf_rev_itoa_base(&dbuffer[78], n, 2);
		set->len = &dbuffer[78] - set->s + 1;
	}
	else
		set->len = 0;
	if (attr->precision > set->len)
		attr->precision -= set->len;
	else
		attr->precision = 0;
	set->width_len = attr->precision + set->len;
	if (attr->flags & F_SHARP && !(attr->flags & F_ZERO))
		set->width_len += 2;
}

static void		pf_fill_conv(t_env *env, t_attr *attr, const t_dbuff_set *set, \
		uint64_t n)
{
	if (attr->flags & F_MINUS)
	{
		if (attr->flags & F_SHARP && n)
		{
			pf_set_char(env, '0');
			pf_set_char(env, 'b');
		}
		pf_set_static_memory(env, '0', attr->precision);
		pf_set_dynamic_memory(env, set->s, set->len);
		if (attr->width > set->width_len)
			pf_set_static_memory(env, ' ', attr->width - set->width_len);
	}
	else
	{
		if (attr->width > set->width_len)
			pf_set_static_memory(env, ' ', attr->width - set->width_len);
		if (attr->flags & F_SHARP && n)
		{
			pf_set_char(env, '0');
			pf_set_char(env, 'b');
		}
		pf_set_static_memory(env, '0', attr->precision);
		pf_set_dynamic_memory(env, set->s, set->len);
	}
}

bool			pf_convert_b(t_env *env, t_attr *attr)
{
	uint64_t		n;
	char			dbuffer[79];
	t_dbuff_set		set;

	if (attr->spec != 'B')
		n = pf_cast_uvalue(&env->arg_list, attr->lenght_mod);
	else
		n = PF_GET_NEXT_ARG(env->arg_list, long);
	pf_handle_overload(attr);
	pf_set_dbuff(dbuffer, &set, attr, n);
	pf_fill_conv(env, attr, &set, n);
	return (0);
}
