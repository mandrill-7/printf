/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:28:17 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/09 16:28:30 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LS_BYTES				0x0101010101010101ULL
#define MS_BYTES				0x8080808080808080ULL
#define LONG_WORD_HAS_ZERO(lw)	(((lw - LS_BYTES) & ~(lw)) & MS_BYTES)
#define TEST_BYTE(x)			if (!ptr[x]) return (ptr - str + x)

static size_t	engine(const char *str, const char *ptr, size_t n)
{
	while (n > 7)
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
		n -= 8;
	}
	while (n)
	{
		if (!*ptr)
			return (ptr - str);
		++ptr;
		--n;
	}
	return (ptr - str);
}

size_t			ft_strnlen(const char *str, size_t n)
{
	const char	*ptr;

	ptr = str;
	while ((uint64_t)ptr % 8 && n)
	{
		if (!*ptr)
			return (ptr - str);
		++ptr;
		--n;
	}
	return (engine(str, ptr, n));
}
