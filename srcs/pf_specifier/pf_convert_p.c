/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:42:19 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:19:05 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define MAX_NUMBER_LEN	16
#define LAST_INDEX		15
#define DIGIT			"0123456789abcdef"
#define BASE			16

uint8_t		ft_itoh(size_t n, char *dbuffer)
{
	uint8_t		off_char;

	off_char = LAST_INDEX;
	while (1)
	{
		dbuffer[off_char--] = DIGIT[n % BASE];
		n /= BASE;
		if (!n)
			return (off_char + 1);
	}
}

bool		pf_convert_p(t_env *env, t_attr *attr)
{
	uint64_t	addr;
	uint8_t		len;
	char		dbuffer[MAX_NUMBER_LEN];
	uint8_t		width_len;

	addr = PF_GET_NEXT_ARG(env->arg_list, uint64_t);
	len = ft_itoh(addr, dbuffer);
	width_len = MAX_NUMBER_LEN - len + 2;
	if (attr->flags & F_MINUS)
	{
		pf_set_char(env, '0');
		pf_set_char(env, 'x');
		pf_set_dynamic_memory(env, &dbuffer[len], (MAX_NUMBER_LEN - len));
		if (attr->width > width_len)
			pf_set_static_memory(env, ' ', attr->width - width_len);
	}
	else
	{
		if (attr->width > width_len)
			pf_set_static_memory(env, ' ', attr->width - width_len);
		pf_set_char(env, '0');
		pf_set_char(env, 'x');
		pf_set_dynamic_memory(env, &dbuffer[len], (MAX_NUMBER_LEN - len));
	}
	return (0);
}
