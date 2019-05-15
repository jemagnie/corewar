/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   number.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 17:02:05 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:49:09 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

int			signe(t_printf *p)
{
	if (p->c)
		return (1);
	if (p->flag & F_DIEZ && (p->arg || p->flag & C_ADDR))
	{
		if (p->flag & (C_OCTAL | C_LOCTAL))
			p->len += write(p->fd, "0", 1);
		else if (p->flag & C_HEXA)
			p->len += write(p->fd, "0x", 2);
		else if (p->flag & C_MHEXA)
			p->len += write(p->fd, "0X", 2);
	}
	if (p->flag & (C_LONG | C_INT))
	{
		if (p->flag & F_PLUS && p->arg >= 0)
			p->len += write(1, "+", 1);
		else if (p->arg < 0)
			p->len += write(1, "-", 1);
		else if (p->flag & F_SPACE)
			p->len += write(1, " ", 1);
	}
	++p->c;
	return (1);
}

static int	precision(t_printf *p)
{
	char	s[32];

	signe(p);
	if (p->flag & F_PRE)
	{
		ft_memset(s, '0', 32);
		while (p->pre > 32)
		{
			p->len += write(p->fd, s, 32);
			p->pre -= 32;
		}
		p->len += write(p->fd, s, p->pre);
	}
	return (1);
}

int			printf_number(t_printf *p, const char *s)
{
	if (p->flag & F_PAD)
	{
		p->pad -= p->n + p->pre;
		if (p->flag & C_NUM_S && (p->flag & (F_PLUS | F_SPACE) || p->arg < 0))
			p->pad -= 1;
		if (p->flag & F_DIEZ && p->flag & C_NUM_B &&
			(p->arg || p->flag & C_ADDR))
			p->pad -= p->flag & (C_OCTAL | C_LOCTAL) ? 1 : 2;
		if (p->flag & F_MINUS)
		{
			precision(p);
			p->len += write(p->fd, s, p->n);
			padding(p);
		}
		else
		{
			padding(p);
			precision(p);
			p->len += write(p->fd, s, p->n);
		}
		return (1);
	}
	precision(p);
	p->len += write(p->fd, s, p->n);
	return (1);
}

int			printf_long(t_printf *p, long n)
{
	char			s[20];
	unsigned long	value;
	int				len;

	len = long_len(*p, n);
	p->n = len;
	value = n < 0 ? -n : n;
	if (p->flag & F_PRE)
	{
		p->pre -= p->n;
		if (p->pre < 0)
		{
			p->flag ^= F_PRE;
			p->pre = 0;
		}
	}
	while (len--)
	{
		s[len] = value % 10 + 48;
		value /= 10;
	}
	return (printf_number(p, (const char *)s));
}

int			printf_ulong_base(t_printf *p, unsigned long n, const int base)
{
	char	s[64];
	int		len;
	int		tmp;
	char	c;

	p->n = ulong_base_len(*p, n, base);
	len = p->n;
	c = (p->flag & C_MHEXA ? 'A' : 'a') - 10;
	if (p->flag & F_PRE && p->flag & F_DIEZ && !n && p->flag & C_NUM_OCT)
		p->pre++;
	if (p->flag & F_PRE)
	{
		p->pre -= p->n;
		if (p->pre < 0 && !(p->pre = 0))
			p->flag ^= F_PRE;
	}
	while (len--)
	{
		tmp = n % base;
		s[len] = tmp + (tmp < 10 ? '0' : c);
		n /= base;
	}
	return (printf_number(p, (const char *)s));
}
