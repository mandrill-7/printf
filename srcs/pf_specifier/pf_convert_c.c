/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:18:28 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:18:33 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool			pf_convert_c(t_env *env, t_attr *attr)
{
	int		c;

	if (attr->spec != 'c' && attr->spec != 'C')
		c = attr->spec;
	else
		c = PF_GET_NEXT_ARG(env->arg_list, int);
	if (attr->lenght_mod == 'l' || attr->spec == 'C')
		return (pf_convert_big_c(env, attr, c));
	pf_insert_string(env, attr, (const char *)&c, 1);
	return (0);
}
