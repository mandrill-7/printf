/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:38:25 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:18:52 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool			pf_convert_n(t_env *env, t_attr *attr)
{
	int64_t		*ptr;

	(void)attr;
	ptr = PF_GET_NEXT_ARG(env->arg_list, int64_t *);
	*ptr = env->output_memory_size;
	return (0);
}
