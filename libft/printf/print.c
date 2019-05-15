/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 17:51:00 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 19:07:08 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

int			padding(t_printf *p)
{
	char	s[32];

	if (p->pad < 0)
		p->pad = 0;
	if (p->flag & F_ZERO && (p->flag & (C_INT | C_LONG)))
		signe(p);
	ft_memset(s, p->flag & F_ZERO ? '0' : ' ', 32);
	while (p->pad > 32)
	{
		write(p->fd, s, 32);
		p->pad -= 32;
		p->len += 32;
	}
	p->len += write(p->fd, s, p->pad);
	return (1);
}

static int	printf_type(t_printf *p, const int flag)
{
	if (flag & C_WCHAR)
		return (printf_wchar(p));
	if (flag & C_WSTRING)
		return (printf_wstring(p));
	if (flag & C_STRING)
		return (printf_string(p));
	if (flag & C_CHAR)
		return (printf_char(p));
	if (flag & (C_INT | C_LONG))
		return (printf_long(p, p->arg));
	if (flag & C_UINT)
		return (printf_ulong_base(p, p->arg, 10));
	if (flag & C_ULONG)
		return (printf_ulong_base(p, p->arg, 10));
	if (flag & (C_HEXA | C_MHEXA))
		return (printf_ulong_base(p, p->arg, 16));
	if (flag & (C_LOCTAL | C_OCTAL))
		return (printf_ulong_base(p, p->arg, 8));
	if (flag & C_BIN)
		return (printf_ulong_base(p, p->arg, 2));
	return (1);
}

static int	printf_arg(t_printf *p, const int flag)
{
	if (flag & (M_LONG | C_STRING | C_WSTRING | C_WCHAR))
		p->arg = va_arg(p->ap, long);
	else if (flag & M_CHAR)
	{
		if (flag & (C_UINT | C_HEXA | C_MHEXA | C_OCTAL))
			p->arg = (unsigned char)va_arg(p->ap, unsigned int);
		else
			p->arg = (char)va_arg(p->ap, int);
	}
	else if (flag & M_SHORT)
	{
		if (flag & (C_UINT | C_HEXA | C_MHEXA | C_OCTAL))
			p->arg = (unsigned short)va_arg(p->ap, unsigned int);
		else
			p->arg = (short)va_arg(p->ap, int);
	}
	else if (flag & (C_UINT | C_HEXA | C_MHEXA | C_OCTAL))
		p->arg = va_arg(p->ap, unsigned int);
	else
		p->arg = va_arg(p->ap, int);
	return (printf_type(p, p->flag));
}

int			verifer(t_printf *p)
{
	if (p->flag & F_SPACE && (p->flag & F_PLUS ||
		!(p->flag & (C_INT | C_LONG))))
		p->flag ^= F_SPACE;
	if (p->flag & F_ZERO && p->flag & (F_MINUS | F_PRE))
		if ((p->flag & (C_STRING | C_PERCENT) && p->flag & F_MINUS) ||
			p->flag & (C_NUM))
			p->flag ^= F_ZERO;
	if (p->flag & (C_LOCTAL | C_ULONG | C_LONG))
		p->flag |= M_LONG;
	if (p->flag & C_ADDR)
		p->flag |= (C_HEXA | F_DIEZ | M_LONG);
	if (p->flag & (C_HEXA | C_MHEXA) && p->flag & F_ZERO && p->flag & F_PAD)
	{
		p->flag |= F_PRE;
		p->pre = p->pad - 2;
	}
	if (p->flag & (F_DIEZ) && p->flag & (C_OCTAL | C_LOCTAL) && p->flag & F_PRE)
		--p->pre;
	if (p->flag & (C_CHAR | C_STRING) && p->flag & M_LONG)
		p->flag |= p->flag & C_CHAR ? C_WCHAR : C_WSTRING;
	if ((short)(p->flag))
		return (printf_arg(p, p->flag));
	else
		return (printf_none(p));
}
