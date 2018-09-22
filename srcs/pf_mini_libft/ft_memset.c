/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 14:17:46 by fchanal           #+#    #+#             */
/*   Updated: 2017/03/11 14:40:19 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LS_BYTES	0x0101010101010101ULL

void	*ft_memset(void *m, int c, size_t len)
{
	const void	*init;
	uint64_t	*long_word;
	uint64_t	ext_char;

	init = (const void *)m;
	while (len % 8)
	{
		*(uint8_t *)m++ = (uint8_t)c;
		--len;
	}
	if (len)
	{
		ext_char = LS_BYTES * (uint8_t)c;
		long_word = (uint64_t *)m;
		while (len)
		{
			*long_word++ = ext_char;
			len -= 8;
		}
	}
	return ((void *)init);
}
