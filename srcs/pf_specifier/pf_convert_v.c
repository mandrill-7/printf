/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_v.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:19:29 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:19:34 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool		pf_convert_v(t_env *env, t_attr *attr)
{
	const char	*string;

	if (attr->precision == -1)
		return (PF_ERROR);
	string = PF_GET_NEXT_ARG(env->arg_list, const char *);
	if (string == NULL)
		pf_insert_string(env, attr, "(null)", 6);
	else
		pf_insert_string(env, attr, string, attr->precision);
	return (0);
}
