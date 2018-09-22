/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_casting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:26:38 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:00 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define PF_HH_VALUE		26728
#define PF_LL_VALUE		27756

uint64_t	pf_cast_uvalue(va_list *arg_list, uint16_t lenght_mod)
{
	if (lenght_mod == 0)
		return (PF_GET_NEXT_ARG(*arg_list, unsigned int));
	else if (lenght_mod == 'h')
		return ((unsigned short)PF_GET_NEXT_ARG(*arg_list, unsigned int));
	else if (lenght_mod == 'l')
		return (PF_GET_NEXT_ARG(*arg_list, unsigned long));
	else if (lenght_mod == 'j')
		return (PF_GET_NEXT_ARG(*arg_list, uintmax_t));
	else if (lenght_mod == 't')
		return (PF_GET_NEXT_ARG(*arg_list, ptrdiff_t));
	else if (lenght_mod == 'z')
		return (PF_GET_NEXT_ARG(*arg_list, size_t));
	else if (lenght_mod == PF_HH_VALUE)
		return ((unsigned char)PF_GET_NEXT_ARG(*arg_list, unsigned int));
	else if (lenght_mod == PF_LL_VALUE)
		return (PF_GET_NEXT_ARG(*arg_list, unsigned long long));
	else
		return (PF_GET_NEXT_ARG(*arg_list, unsigned int));
}

int64_t		pf_cast_svalue(va_list *arg_list, uint16_t lenght_mod)
{
	if (lenght_mod == 0)
		return (PF_GET_NEXT_ARG(*arg_list, int));
	else if (lenght_mod == 'h')
		return ((short)PF_GET_NEXT_ARG(*arg_list, int));
	else if (lenght_mod == 'l')
		return (PF_GET_NEXT_ARG(*arg_list, long));
	else if (lenght_mod == 'j')
		return (PF_GET_NEXT_ARG(*arg_list, intmax_t));
	else if (lenght_mod == 't')
		return (PF_GET_NEXT_ARG(*arg_list, ptrdiff_t));
	else if (lenght_mod == 'z')
		return (PF_GET_NEXT_ARG(*arg_list, size_t));
	else if (lenght_mod == PF_HH_VALUE)
		return ((char)PF_GET_NEXT_ARG(*arg_list, int));
	else if (lenght_mod == PF_LL_VALUE)
		return (PF_GET_NEXT_ARG(*arg_list, long long));
	else
		return (PF_GET_NEXT_ARG(*arg_list, int));
}
