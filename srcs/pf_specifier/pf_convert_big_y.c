/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_big_y.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:15:13 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:18:15 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool		pf_convert_big_y(t_env *env, t_attr *attr)
{
	bool		b;

	b = (bool)PF_GET_NEXT_ARG(env->arg_list, int);
	if (b == true)
		pf_insert_string(env, attr, "TRUE", 4);
	else
		pf_insert_string(env, attr, "FALSE", 5);
	return (0);
}
