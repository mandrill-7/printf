/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:46:41 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:19:40 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PF_0X_VALUE		0x7830

static char		*pf_sharp_conv(char conv[4], unsigned char c)
{
	*(uint16_t *)conv = PF_0X_VALUE;
	conv[2] = FT_HEX_DIGIT[c / 16];
	conv[3] = FT_HEX_DIGIT[c % 16];
	return (conv);
}

static char		*pf_classic_conv(char conv[4], unsigned char c)
{
	conv[0] = FT_HEX_DIGIT[c / 16];
	conv[1] = FT_HEX_DIGIT[c % 16];
	return (conv);
}

bool			pf_convert_w(t_env *env, t_attr *attr)
{
	unsigned char	c;
	char			conv[4];

	c = (unsigned char)PF_GET_NEXT_ARG(env->arg_list, int);
	if (ft_isprint(c))
		pf_insert_string(env, attr, (const char *)&c, 1);
	else
	{
		if (attr->flags & F_SHARP)
			pf_insert_string(env, attr, pf_sharp_conv(conv, c), 4);
		else
			pf_insert_string(env, attr, pf_classic_conv(conv, c), 2);
	}
	return (0);
}
