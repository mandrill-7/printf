/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 15:43:31 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:21 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_init_env(t_env *env)
{
	env->output_memory_size = 0;
	env->buffer_pos = 0;
	env->color_current = 0;
	env->color_base = 0;
}

bool			pf_insert_conversion(t_env *env, t_attr *attr, \
		const char **format)
{
	bool		(*func)(t_env *, t_attr *);

	if (**format == '{')
		pf_insert_color(env, format);
	attr->flags = pf_get_flags(format);
	pf_get_width(format, &env->arg_list, &attr->width, &attr->flags);
	pf_get_precision(format, &env->arg_list, &attr->precision);
	attr->lenght_mod = pf_get_lenght_mod(format);
	attr->spec = **format;
	if (attr->spec > 127)
		attr->spec = 1;
	func = g_specifier_table[attr->spec];
	if (func)
	{
		if (func(env, attr))
			return (PF_ERROR);
		pf_check_color(env);
		if (**format != '\0')
			++(*format);
	}
	return (0);
}

bool			pf_parse_format(t_env *env, const char *format)
{
	const char	*current;
	t_attr		attr;

	while (1)
	{
		current = ft_strchr_zero(format, '%');
		if (current != format)
		{
			pf_set_dynamic_memory(env, format, (current - format));
			format = current;
		}
		if (*format++ == '%')
		{
			if (pf_insert_conversion(env, &attr, &format) == PF_ERROR)
			{
				va_end(env->arg_list);
				return (PF_ERROR);
			}
		}
		else
			return (0);
	}
}

int				ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_env			env;

	if (!format)
		return (-1);
	pf_init_env(&env);
	env.fd = fd;
	va_copy(env.arg_list, ap);
	if (*format == '{')
	{
		pf_insert_color(&env, &format);
		env.color_base = env.color_current;
	}
	if ((pf_parse_format(&env, format)) == PF_ERROR)
		return (-1);
	if (env.color_base != 0)
		pf_set_dynamic_memory(&env, C_NONE, 4);
	va_end(env.arg_list);
	write(fd, env.buffer, env.buffer_pos);
	return (env.output_memory_size);
}
