/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:16:44 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:16:48 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define PF_FLAG_TABLE_LEN	49

static const uint8_t	g_flag_table[PF_FLAG_TABLE_LEN] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, F_SPACE, 0, 0, F_SHARP, 0, 0, 0,
	F_QUOTE, 0, 0, 0, F_PLUS, 0, F_MINUS, 0, 0, F_ZERO
};

uint8_t		pf_get_flags(const char **s)
{
	uint8_t			flags;
	unsigned char	c;

	flags = 0;
	while (1)
	{
		c = **s;
		if (c >= PF_FLAG_TABLE_LEN || g_flag_table[c] == 0)
			break ;
		flags |= g_flag_table[c];
		++*s;
	}
	return (flags);
}

void		pf_get_width(const char **s, va_list *arg_list, int *width, \
		uint8_t *flags)
{
	if (**s == '*')
	{
		*width = PF_GET_NEXT_ARG(*arg_list, int);
		if (*width < 0)
		{
			*flags |= F_MINUS;
			*width *= -1;
		}
		++*s;
	}
	else
		*width = ft_get_nbr(s);
}

void		pf_get_precision(const char **s, va_list *arg_list, int *precision)
{
	if (**s == '.')
	{
		++*s;
		if (**s == '*')
		{
			*precision = PF_GET_NEXT_ARG(*arg_list, int);
			++*s;
		}
		else
			*precision = ft_get_nbr(s);
	}
	else
		*precision = -1;
}

uint16_t	pf_get_lenght_mod(const char **s)
{
	const char		*lm;
	unsigned char	c;

	lm = *s;
	while (1)
	{
		c = **s;
		if (c >= PF_ASCII_LEN || g_specifier_table[c])
			break ;
		++*s;
	}
	if (*s == lm)
		return (0);
	else if (*s - lm == 1)
		return (*lm);
	else
		return (*(uint16_t *)lm);
}
