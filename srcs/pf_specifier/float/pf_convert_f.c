/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:46:29 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:38 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FBUFF_SIZE		512
#define DBL_MAX_DOT		311
#define PRECISION_MAX	(FBUFF_SIZE - DBL_MAX_DOT)

static int		pf_set_dbuff(char *fbuffer, t_attr *attr, double n)
{
	uint16_t	len;
	uint16_t	dot_pos;

	len = 0;
	pf_insert_integer_part(n, fbuffer, &len);
	dot_pos = len;
	pf_insert_frac_part((n - ft_get_dint_part(n)), attr->precision + 1, \
			fbuffer, &len);
	pf_round(fbuffer, &len, &dot_pos);
	if (attr->precision || attr->flags & F_SHARP)
	{
		pf_insert_dot(fbuffer, len - 1, dot_pos);
		return (len);
	}
	else
		return (len - 1);
}

static void		pf_handle_overload(t_attr *attr, double *n, t_fset *set)
{
	if (*n < 0)
	{
		*n *= -1;
		set->ext_signed_char = '-';
	}
	else if (attr->flags & F_PLUS)
		set->ext_signed_char = '+';
	else if (attr->flags & F_SPACE)
		set->ext_signed_char = ' ';
	else
		set->ext_signed_char = 0;
	if (attr->precision == -1)
		attr->precision = 6;
	else if (attr->precision > PRECISION_MAX)
	{
		set->sup_prec = attr->precision - PRECISION_MAX;
		attr->precision = PRECISION_MAX;
	}
}

static void		pf_fill_conv(t_env *env, t_attr *attr, char *fbuffer, \
		t_fset set)
{
	if (attr->flags & F_MINUS)
	{
		if (set.ext_signed_char != 0)
			pf_set_char(env, set.ext_signed_char);
		pf_set_dynamic_memory(env, fbuffer, set.len);
		if (set.sup_prec)
			pf_set_static_memory(env, '0', set.sup_prec);
		if (attr->width > set.width_len)
			pf_set_static_memory(env, ' ', attr->width - set.width_len);
	}
	else
	{
		if (!(attr->flags & F_ZERO) && attr->width > set.width_len)
			pf_set_static_memory(env, ' ', attr->width - set.width_len);
		if (set.ext_signed_char != 0)
			pf_set_char(env, set.ext_signed_char);
		if (attr->flags & F_ZERO && attr->width > set.width_len)
			pf_set_static_memory(env, '0', attr->width - set.width_len);
		pf_set_dynamic_memory(env, fbuffer, set.len);
		if (set.sup_prec)
			pf_set_static_memory(env, '0', set.sup_prec);
	}
}

bool			pf_convert_f(t_env *env, t_attr *attr)
{
	double	n;
	char	fbuffer[FBUFF_SIZE];
	t_fset	set;

	set.sup_prec = 0;
	n = PF_GET_NEXT_ARG(env->arg_list, double);
	pf_handle_overload(attr, &n, &set);
	set.len = pf_set_dbuff(fbuffer, attr, n);
	set.width_len = set.len + (set.ext_signed_char != 0) + set.sup_prec;
	pf_fill_conv(env, attr, fbuffer, set);
	return (0);
}
