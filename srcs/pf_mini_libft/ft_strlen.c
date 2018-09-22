/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 22:11:03 by fchanal           #+#    #+#             */
/*   Updated: 2017/03/16 07:42:04 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LS_BYTES				0x0101010101010101ULL
#define MS_BYTES				0x8080808080808080ULL
#define LONG_WORD_HAS_ZERO(lw)	(((lw - LS_BYTES) & ~(lw)) & MS_BYTES)
#define TEST_BYTE(x)			if (!ptr[x]) return (ptr - str + x)

size_t	ft_strlen(const char *str)
{
	const char		*ptr;

	ptr = str;
	while ((uint64_t)ptr % 8)
	{
		if (!*ptr)
			return (ptr - str);
		++ptr;
	}
	while (1)
	{
		if (LONG_WORD_HAS_ZERO(*(uint64_t*)ptr))
		{
			TEST_BYTE(0);
			TEST_BYTE(1);
			TEST_BYTE(2);
			TEST_BYTE(3);
			TEST_BYTE(4);
			TEST_BYTE(5);
			TEST_BYTE(6);
			TEST_BYTE(7);
		}
		ptr += 8;
	}
}
