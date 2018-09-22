/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 14:59:20 by fchanal           #+#    #+#             */
/*   Updated: 2017/03/11 14:28:18 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *m1, const void *m2, size_t len)
{
	const void	*init;
	uint64_t	*long_word_1;
	uint64_t	*long_word_2;

	init = m1;
	while (len % 8)
	{
		*(uint8_t *)m1++ = *(uint8_t *)m2++;
		--len;
	}
	if (len)
	{
		long_word_1 = (uint64_t *)m1;
		long_word_2 = (uint64_t *)m2;
		while (len)
		{
			*long_word_1++ = *long_word_2++;
			len -= 8;
		}
	}
	return ((void *)init);
}
