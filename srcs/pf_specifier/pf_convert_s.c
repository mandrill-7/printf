/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:19:12 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:19:16 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool			pf_convert_s(t_env *env, t_attr *attr)
{
	const char *string;

	string = PF_GET_NEXT_ARG(env->arg_list, const char *);
	if (string == NULL)
	{
		pf_insert_string(env, attr, "(null)", ft_strnlen("(null)", \
					attr->precision));
		return (0);
	}
	else if (attr->lenght_mod == 'l' || attr->spec == 'S')
		return (pf_convert_big_s(env, attr, (const wchar_t *)string));
	else
	{
		if (attr->precision != -1)
			pf_insert_string(env, attr, string, ft_strnlen(string, \
						attr->precision));
		else
			pf_insert_string(env, attr, string, ft_strlen(string));
		return (0);
	}
}
