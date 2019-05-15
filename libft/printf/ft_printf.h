/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 16:43:48 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 15:15:50 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define C_STRING	(1 << 0)
# define C_WSTRING	(1 << 1)
# define C_ADDR		(1 << 2)
# define C_INT		(1 << 3)
# define C_LONG		(1 << 4)
# define C_ULONG	(1 << 5)
# define C_OCTAL	(1 << 6)
# define C_LOCTAL	(1 << 7)
# define C_UINT		(1 << 8)
# define C_HEXA		(1 << 9)
# define C_MHEXA	(1 << 10)
# define C_CHAR		(1 << 11)
# define C_WCHAR	(1 << 12)
# define C_DOUBLE	(1 << 13)
# define C_BIN		(1 << 14)
# define C_OTHER	(1 << 15)
# define C_PERCENT	(1 << 16)

# define C_NUM_S	(C_INT | C_LONG)
# define C_NUM_DEC	(C_UINT | C_INT | C_LONG | C_ULONG)
# define C_NUM_OCT	(C_OCTAL | C_LOCTAL)
# define C_NUM_HEX	(C_HEXA | C_MHEXA)
# define C_NUM_B 	(C_NUM_HEX | C_NUM_OCT)
# define C_NUM		(C_NUM_DEC | C_NUM_HEX | C_NUM_OCT)

# define M_CHAR		(1 << 21)
# define M_SHORT	(1 << 22)
# define M_LONG		(1 << 23)
# define M_BIGL		(1 << 24)

# define F_PAD		(1 << 31)
# define F_SPACE	(1 << 30)
# define F_ZERO		(1 << 29)
# define F_PRE		(1 << 28)
# define F_PLUS		(1 << 27)
# define F_MINUS	(1 << 26)
# define F_DIEZ		(1 << 25)

typedef struct	s_printf
{
	int			fd;
	va_list		ap;
	char		*format;
	long		arg;
	void		*s;
	char		buf[64];
	int			i;
	int			c;
	int			n;
	int			pre;
	int			pad;
	int			flag;
	int			len;
}				t_printf;

/*
**	file descriptor
**	va_list
**	value_arg;
**	buff format
**	buff to print
**	char to print
**	len to print
**	value of precision
**	value of padding
**	len to return
**	flag for parsing
*/

int				padding(t_printf *p);
int				parser(t_printf *p);
int				verifer(t_printf *p);
int				printf_wstring(t_printf *p);
int				printf_string(t_printf *p);
int				printf_wchar(t_printf *p);
int				printf_char(t_printf *p);
int				printf_none(t_printf *p);
int				printf_long(t_printf *p, long n);
int				printf_ulong_base(t_printf *p, unsigned long n, const int base);
int				signe(t_printf *p);
int				ulong_base_len(t_printf p, unsigned long n, const int base);
int				long_len(t_printf p, const long n);

#endif
