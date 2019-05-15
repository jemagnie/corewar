/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 18:09:56 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:49:17 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

int		printf_string(t_printf *p)
{
	p->s = p->arg ? (char *)p->arg : "(null)";
	p->n = ft_strlen(p->s);
	p->n = p->flag & F_PRE && p->pre < p->n ? p->pre : p->n;
	p->pad -= p->n;
	if (p->flag & F_PAD)
	{
		if (p->flag & F_MINUS)
		{
			p->len += write(p->fd, p->s, p->n);
			padding(p);
		}
		else
		{
			padding(p);
			p->len += write(p->fd, p->s, p->n);
		}
	}
	else
		p->len += write(p->fd, p->s, p->n);
	return (1);
}

int		printf_char(t_printf *p)
{
	p->c = (char)p->arg;
	++p->n;
	--p->pad;
	if (p->flag & F_PAD)
	{
		if (p->flag & F_MINUS)
		{
			p->len += write(p->fd, &p->c, p->n);
			padding(p);
		}
		else
		{
			padding(p);
			p->len += write(p->fd, &p->c, p->n);
		}
	}
	else
		p->len += write(p->fd, &p->c, p->n);
	return (1);
}

int		printf_wchar(t_printf *p)
{
	p->c = (wchar_t)p->arg;
	p->n = ft_wclen(p->c);
	p->pad -= p->n;
	if (p->flag & F_PAD)
	{
		if (p->flag & F_MINUS)
		{
			p->len += ft_putwchar(p->c);
			padding(p);
		}
		else
		{
			padding(p);
			p->len += ft_putwchar(p->c);
		}
	}
	else
		p->len += ft_putwchar(p->c);
	return (1);
}

int		printf_wstring(t_printf *p)
{
	if (!p->arg)
		return (printf_string(p));
	p->s = (void *)p->arg;
	p->n = p->flag & F_PRE ? ft_nwstrlen(p->s, p->pre) : ft_wstrlen(p->s);
	p->pad -= p->n;
	p->pad = p->pad < 0 ? 0 : p->pad;
	if (p->flag & F_PAD)
	{
		if (p->flag & F_MINUS)
		{
			p->len += ft_putnwstr((wchar_t *)p->s, p->n);
			padding(p);
		}
		else
		{
			padding(p);
			p->len += ft_putnwstr((wchar_t *)p->s, p->n);
		}
	}
	else
		p->len += ft_putnwstr((wchar_t *)p->s, p->n);
	return (1);
}

int		printf_none(t_printf *p)
{
	--p->pad;
	if (p->flag & F_PAD)
	{
		if (p->flag & F_MINUS)
		{
			p->len += write(p->fd, p->format, 1);
			padding(p);
		}
		else
		{
			padding(p);
			p->len += write(p->fd, p->format, 1);
		}
	}
	else
		p->len += write(p->fd, p->format, 1);
	return (1);
}
