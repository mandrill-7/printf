/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 15:59:41 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:16:23 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	pf_null_spec(t_env *s, t_attr *attr)
{
	(void)s;
	(void)attr;
	return (0);
}

void	pf_insert_string(t_env *env, t_attr *attr, const char *str, \
		size_t len)
{
	if (attr->flags & F_MINUS)
	{
		pf_set_dynamic_memory(env, str, len);
		if ((size_t)attr->width > len)
			pf_set_static_memory(env, ' ', attr->width - len);
	}
	else
	{
		if ((size_t)attr->width > len)
			pf_set_static_memory(env, ' ', attr->width - len);
		pf_set_dynamic_memory(env, str, len);
	}
}
