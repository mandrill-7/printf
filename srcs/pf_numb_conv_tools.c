/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_numb_conv_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:30:09 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:16:40 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_rev_itoa_base_up(char *buffer, uint64_t n, uint8_t base)
{
	while (1)
	{
		*buffer = FT_HEXU_DIGIT[n % base];
		n /= base;
		if (!n)
			return (buffer);
		--buffer;
	}
}

char	*pf_rev_itoa_base(char *buffer, uint64_t n, uint8_t base)
{
	while (1)
	{
		*buffer = FT_HEX_DIGIT[n % base];
		n /= base;
		if (!n)
			return (buffer);
		--buffer;
	}
}

char	*pf_rev_itoa_base_quote_up(char *buffer, uint64_t n, uint8_t base, \
		uint8_t ref_quote)
{
	uint8_t		q;

	q = 0;
	while (1)
	{
		*buffer-- = FT_HEXU_DIGIT[n % base];
		n /= base;
		if (!n)
			return (buffer + 1);
		if (!((++q) % ref_quote))
			*buffer-- = ',';
	}
}

char	*pf_rev_itoa_base_quote(char *buffer, uint64_t n, uint8_t base, \
		uint8_t ref_quote)
{
	uint8_t		q;

	q = 0;
	while (1)
	{
		*buffer-- = FT_HEX_DIGIT[n % base];
		n /= base;
		if (!n)
			return (buffer + 1);
		if (!((++q) % ref_quote))
			*buffer-- = ',';
	}
}
