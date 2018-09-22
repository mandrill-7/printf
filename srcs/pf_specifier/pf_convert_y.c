/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_y.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:20:03 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:20:05 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool			pf_convert_y(t_env *env, t_attr *attr)
{
	bool		b;

	b = (bool)PF_GET_NEXT_ARG(env->arg_list, int);
	if (b == true)
		pf_insert_string(env, attr, "true", 4);
	else
		pf_insert_string(env, attr, "false", 4);
	return (0);
}
