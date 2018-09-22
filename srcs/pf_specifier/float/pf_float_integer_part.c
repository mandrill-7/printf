/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_integer_part.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:25:24 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:48 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define LAST_INDEX		511
#define DOUBLE_BIAIS	1023

static void		ft_get_len(double n, uint16_t *len, double *log)
{
	while ((n = ft_get_dint_part(n / 10)) > 0)
	{
		++(*len);
		*log *= 10;
	}
}

static int		ft_get_asc(double number, uint16_t len)
{
	while (len--)
		number /= 10;
	return ((int)(number * 10));
}

static void		pf_print_small_integer(double n, char *float_buffer, \
		uint16_t *pindex)
{
	uint64_t		integer;
	uint16_t		rev_index;

	rev_index = LAST_INDEX;
	integer = (uint64_t)n;
	while (1)
	{
		float_buffer[rev_index--] = FT_DIGIT[integer % 10];
		integer /= 10;
		if (!integer)
			break ;
	}
	*pindex = LAST_INDEX - rev_index;
	ft_memcpy(float_buffer, &float_buffer[rev_index + 1], *pindex);
}

static void		pf_print_big_integer(double n, char *float_buffer, \
		uint16_t *pindex)
{
	uint16_t	len;
	double		log;
	uint8_t		asc;

	len = 1;
	log = 1;
	ft_get_len(n, &len, &log);
	while (len)
	{
		asc = ft_get_asc(n, len);
		float_buffer[(*pindex)++] = FT_DIGIT[asc];
		n -= log * asc;
		--len;
		log /= 10;
	}
}

void			pf_insert_integer_part(double n, char *fbuffer, \
		uint16_t *pindex)
{
	if ((ft_dexp(n) - DOUBLE_BIAIS) < 64)
		pf_print_small_integer(n, fbuffer, pindex);
	else
		pf_print_big_integer(n, fbuffer, pindex);
}
