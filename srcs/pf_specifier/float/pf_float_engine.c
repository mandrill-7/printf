/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_engine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:22:20 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:43 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_shift_buffer(char *fbuffer, uint16_t start, uint16_t end)
{
	while (end >= start)
	{
		fbuffer[end + 1] = fbuffer[end];
		--end;
	}
}

void			pf_insert_dot(char *fbuffer, uint16_t shift_index, \
		uint16_t dot_pos)
{
	pf_shift_buffer(fbuffer, dot_pos, shift_index);
	fbuffer[dot_pos] = '.';
}

void			pf_round(char *fbuffer, uint16_t *pindex, uint16_t *pdot_pos)
{
	uint16_t		rev_index;

	rev_index = *pindex - 1;
	fbuffer[rev_index] += 5;
	while ((fbuffer[rev_index]) > '9')
	{
		if (rev_index)
		{
			fbuffer[rev_index] = '0';
			++fbuffer[--rev_index];
		}
		else
		{
			fbuffer[rev_index] = '1';
			++(*pindex);
			++(*pdot_pos);
		}
	}
}

void			pf_insert_frac_part(double n, uint16_t precision, \
		char *fbuffer, uint16_t *pindex)
{
	while (precision--)
	{
		n *= 10;
		fbuffer[(*pindex)++] = (((uint64_t)n) + 48);
		n -= (uint64_t)n;
	}
}
