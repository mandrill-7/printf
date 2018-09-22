/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:18:43 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:21:48 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_insert_hex(t_env *env, const unsigned char *m, size_t size)
{
	uint8_t		space;
	uint8_t		count;

	space = 40;
	count = 0;
	if (size > 16)
		size = 16;
	while (size)
	{
		pf_set_char(env, FT_HEX_DIGIT[*m / 16]);
		pf_set_char(env, FT_HEX_DIGIT[*m % 16]);
		if (!(++count % 2))
		{
			--space;
			pf_set_char(env, ' ');
		}
		++m;
		--size;
		space -= 2;
	}
	while (space--)
		pf_set_char(env, ' ');
}

static void		pf_insert_ascii(t_env *env, const unsigned char *m, size_t size)
{
	if (size > 16)
		size = 16;
	while (size)
	{
		if (*m > 31 && *m < 127)
			pf_set_char(env, *m);
		else
			pf_set_char(env, '.');
		++m;
		--size;
	}
	pf_set_char(env, '\n');
}

bool			pf_convert_m(t_env *env, t_attr *attr)
{
	void	*m;
	int		count;

	if (attr->precision == -1)
		return (PF_ERROR);
	m = PF_GET_NEXT_ARG(env->arg_list, void *);
	count = 0;
	while (count < attr->precision)
	{
		pf_insert_hex(env, (const unsigned char *)(m + count), \
				(attr->precision - count));
		pf_insert_ascii(env, (const unsigned char *)(m + count), \
				(attr->precision - count));
		count += 16;
	}
	return (0);
}
