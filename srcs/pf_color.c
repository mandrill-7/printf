/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:35:30 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:16:55 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_color	g_color[8] =
{
	{C_NONE, 4}, {C_GREY, 7}, {C_RED, 7},
	{C_GREEN, 7}, {C_YELLOW, 7}, {C_BLUE, 7}, {C_MAGENTA, 7}, {C_CYAN, 7}
};

static int8_t			pf_get_color_index(const char *format, size_t size)
{
	if (!(ft_memcmp("GREY", format, size)))
		return (1);
	else if (!(ft_memcmp("RED", format, size)))
		return (2);
	else if (!(ft_memcmp("GREEN", format, size)))
		return (3);
	else if (!(ft_memcmp("YELLOW", format, size)))
		return (4);
	else if (!(ft_memcmp("BLUE", format, size)))
		return (5);
	else if (!(ft_memcmp("MAGENTA", format, size)))
		return (6);
	else if (!(ft_memcmp("CYAN", format, size)))
		return (7);
	else
		return (-1);
}

void					pf_insert_color(t_env *env, const char **format)
{
	const char	*close_bracket;
	int8_t		color_index;

	if ((close_bracket = ft_strchr((*format), '}')) != NULL)
		if ((color_index = pf_get_color_index(((*format) + 1),
						(close_bracket - (*format) - 1))) != -1)
		{
			env->color_current = color_index;
			*format = close_bracket + 1;
			pf_set_dynamic_memory(env, g_color[env->color_current].pattern,
					g_color[env->color_current].pattern_size);
		}
}

void					pf_check_color(t_env *env)
{
	if (env->color_current != env->color_base)
	{
		env->color_current = env->color_base;
		pf_set_dynamic_memory(env, g_color[env->color_current].pattern,
				g_color[env->color_current].pattern_size);
	}
}
