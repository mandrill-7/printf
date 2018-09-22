/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unicode_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:16:28 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:16:31 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_handle_four_bytes(t_env *env, wint_t c)
{
	pf_set_char(env, (c >> 18) | 0xF0);
	pf_set_char(env, ((c >> 12) | 0x80) & 0xBF);
	pf_set_char(env, ((c >> 6) | 0x80) & 0xBF);
	pf_set_char(env, (c | 0x80) & 0xBF);
}

void		pf_handle_three_bytes(t_env *env, wint_t c)
{
	pf_set_char(env, (c >> 12) | 0xE0);
	pf_set_char(env, ((c >> 6) | 0x80) & 0xBF);
	pf_set_char(env, (c | 0x80) & 0xBF);
}

void		pf_handle_two_bytes(t_env *env, wint_t c)
{
	pf_set_char(env, (c >> 6) | 0xC0);
	pf_set_char(env, (c | 0x80) & 0xBF);
}

void		pf_handle_one_byte(t_env *env, wint_t c)
{
	pf_set_char(env, c);
}
