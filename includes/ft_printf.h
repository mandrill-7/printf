/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:15:59 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/13 11:29:30 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

# define PF_BUFFER_SIZE		512

# define PF_GET_NEXT_ARG(al, type) (type)va_arg(al, type)
# define PF_CAST_VALUE(value, type) value = (type)value
# define PF_ERROR	1

# define BYTE_MAX_VALUE				0x000000FF
# define EIGHT_BITS_MIN_VALUE		0x00000080
# define TWELVE_BITS_MIN_VALUE		0x00000800
# define SEVENTEEN_BITS_MIN_VALUE	0x00010000
# define TWENTYTWO_BITS_MIN_VALUE	0x00400000
# define IS_DEMI_CODETS(n)			(n > 0x0000D7FF && n < 0x0000E000)

# define PF_MAX_UPPER_CASE_LETTER 	90
# define PF_ASCII_LEN	128

typedef struct s_p_attr		t_p_attr;
typedef struct s_u_attr		t_u_attr;
typedef struct s_env		t_env;
typedef struct s_color		t_color;
typedef struct s_dbuff_set	t_dbuff_set;
typedef struct s_attr		t_attr;
typedef struct s_fset		t_fset;

# define F_PLUS		0x01
# define F_MINUS	0x02
# define F_SHARP	0x04
# define F_SPACE	0x08
# define F_QUOTE	0x10
# define F_ZERO		0x20

struct		s_env
{
	int			output_memory_size;
	char		buffer[PF_BUFFER_SIZE];
	uint32_t	buffer_pos;
	va_list		arg_list;
	int			fd;
	uint8_t		color_base;
	uint8_t		color_current;
};

struct		s_color
{
	char		pattern[7];
	uint8_t		pattern_size;
};

struct		s_attr
{
	uint8_t			flags;
	int				width;
	int				precision;
	uint16_t		lenght_mod;
	unsigned char	spec;
};

struct		s_dbuff_set
{
	const char	*s;
	uint8_t		len;
	uint8_t		width_len;
};

struct		s_fset
{
	uint16_t	len;
	char		ext_signed_char;
	uint16_t	width_len;
	int			sup_prec;
};

int			ft_vdprintf(int fd, const char *format, va_list ap);
int			ft_vprintf(const char *format, va_list ap);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_printf(const char *format, ...);
bool		pf_insert_conversion(t_env *data, t_attr *attr, \
		const char **format);
bool		pf_parse_format(t_env *data, const char *format);
void		pf_set_dynamic_memory(t_env *data, const char *m, size_t size);
void		pf_set_static_memory(t_env *data, char st_char, size_t size);
void		pf_set_char(t_env *data, unsigned char c);
void		pf_insert_color(t_env *data, const char **format);
void		pf_check_color(t_env *data);
void		pf_handle_four_bytes(t_env *data, wint_t c);
void		pf_handle_three_bytes(t_env *data, wint_t c);
void		pf_handle_two_bytes(t_env *data, wint_t c);
void		pf_handle_one_byte(t_env *data, wint_t c);
bool		pf_null_spec(t_env *data, t_attr *attr);
bool		pf_convert_m(t_env *data, t_attr *attr);
bool		pf_convert_big_m(t_env *data, t_attr *attr);
bool		pf_convert_c(t_env *data, t_attr *attr);
bool		pf_convert_s(t_env *data, t_attr *attr);
bool		pf_convert_y(t_env *data, t_attr *attr);
bool		pf_convert_v(t_env *data, t_attr *attr);
bool		pf_convert_p(t_env *data, t_attr *attr);
bool		pf_convert_d(t_env *data, t_attr *attr);
bool		pf_convert_u(t_env *data, t_attr *attr);
bool		pf_convert_x(t_env *data, t_attr *attr);
bool		pf_convert_o(t_env *data, t_attr *attr);
bool		pf_convert_b(t_env *data, t_attr *attr);
bool		pf_convert_n(t_env *data, t_attr *attr);
bool		pf_convert_w(t_env *data, t_attr *attr);
bool		pf_convert_f(t_env *data, t_attr *attr);
bool		pf_convert_big_y(t_env *data, t_attr *attr);
bool		pf_convert_big_w(t_env *data, t_attr *attr);
bool		pf_convert_big_c(t_env *data, t_attr *attr, wint_t c);
bool		pf_convert_big_s(t_env *data, t_attr *attr, const wchar_t *string);
void		pf_parse_attr(t_env *data, t_attr *attr, const char **format);
uint8_t		pf_get_flags(const char **s);
uint16_t	pf_get_lenght_mod(const char **s);
void		pf_get_width(const char **s, va_list *arg_list, int *width, \
		uint8_t *flags);
void		pf_get_precision(const char **s, va_list *arg_list, int *precision);
int64_t		pf_cast_svalue(va_list *arg_list, uint16_t lenght_mod);
uint64_t	pf_cast_uvalue(va_list *arg_list, uint16_t lenght_mod);
char		*pf_rev_itoa_base_up(char *buffer, uint64_t n, uint8_t base);
char		*pf_rev_itoa_base(char *buffer, uint64_t n, uint8_t base);
char		*pf_rev_itoa_base_quote_up(char *buffer, uint64_t n, uint8_t base, \
		uint8_t ref_quote);
char		*pf_rev_itoa_base_quote(char *buffer, uint64_t n, uint8_t base, \
		uint8_t ref_quote);
void		pf_insert_string(t_env *data, t_attr *attr, const char *str, \
		size_t len);
void		pf_round(char *fbuffer, uint16_t *pindex, uint16_t *pdot_pos);
void		pf_insert_dot(char *fbuffer, uint16_t shift_index, \
		uint16_t dot_pos);
void		pf_insert_frac_part(double n, uint16_t precision, \
		char *float_buffer, uint16_t *pindex);
void		pf_insert_integer_part(double n, char *fbuffer, uint16_t *pindex);

static bool (*g_specifier_table[PF_ASCII_LEN])(t_env *, t_attr *) =
{
	pf_null_spec,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	0,
	pf_convert_c,
	pf_convert_c,
	0,
	0,
	pf_convert_c,
	pf_convert_c,
	0,
	pf_convert_c,
	pf_convert_c,
	0,
	0,
	0,
	0,
	0,
	pf_convert_c,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	0,
	pf_convert_b,
	pf_convert_c,
	pf_convert_d,
	0,
	pf_convert_f,
	0,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	0,
	pf_convert_big_m,
	pf_convert_c,
	pf_convert_o,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_s,
	pf_convert_c,
	pf_convert_u,
	pf_convert_c,
	pf_convert_big_w,
	pf_convert_x,
	pf_convert_big_y,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	0,
	0,
	pf_convert_b,
	pf_convert_c,
	pf_convert_d,
	0,
	pf_convert_f,
	0,
	0,
	pf_convert_d,
	0,
	pf_convert_c,
	0,
	pf_convert_m,
	pf_convert_n,
	pf_convert_o,
	pf_convert_p,
	0,
	pf_convert_c,
	pf_convert_s,
	0,
	pf_convert_u,
	pf_convert_v,
	pf_convert_w,
	pf_convert_x,
	pf_convert_y,
	0,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c,
	pf_convert_c
};

#endif
