/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dint_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 07:21:01 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/08 14:37:57 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_get_dint_part(double number)
{
	if (ft_dexp(number) > 1086)
		return (number);
	if (number < 0)
	{
		number *= -1;
		number = (uint64_t)number;
		return (number * -1);
	}
	else
	{
		number = (uint64_t)number;
		return (number);
	}
}
