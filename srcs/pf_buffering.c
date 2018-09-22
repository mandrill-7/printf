/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buffering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:17:05 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:17:10 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_set_char(t_env *env, unsigned char c)
{
	if (env->buffer_pos == PF_BUFFER_SIZE)
	{
		write(env->fd, env->buffer, PF_BUFFER_SIZE);
		env->buffer_pos = 0;
	}
	env->buffer[(env->buffer_pos)++] = c;
	++env->output_memory_size;
}

void	pf_set_static_memory(t_env *env, char st_char, size_t size)
{
	size_t		rest;

	env->output_memory_size += size;
	while (size)
	{
		rest = PF_BUFFER_SIZE - env->buffer_pos;
		if (size <= rest)
		{
			ft_memset(&(env->buffer[env->buffer_pos]), st_char, size);
			env->buffer_pos += size;
			return ;
		}
		else
		{
			ft_memset(&(env->buffer[env->buffer_pos]), st_char, rest);
			write(env->fd, env->buffer, PF_BUFFER_SIZE);
			env->buffer_pos = 0;
			size -= rest;
		}
	}
}

void	pf_set_dynamic_memory(t_env *env, const char *m, size_t size)
{
	size_t		rest;

	env->output_memory_size += size;
	while (size)
	{
		rest = PF_BUFFER_SIZE - env->buffer_pos;
		if (size <= rest)
		{
			ft_memcpy(&(env->buffer[env->buffer_pos]), m, size);
			env->buffer_pos += size;
			return ;
		}
		else
		{
			ft_memcpy(&(env->buffer[env->buffer_pos]), m, rest);
			write(env->fd, env->buffer, PF_BUFFER_SIZE);
			env->buffer_pos = 0;
			m += rest;
			size -= rest;
		}
	}
}
