/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 20:01:16 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:49:06 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

static int	printf_buf(t_printf *p, char b)
{
	if (p->i == 32)
	{
		p->len += write(p->fd, p->buf, p->i);
		p->i = 0;
		p->buf[p->i++] = *p->format;
	}
	else if (b)
	{
		p->len += write(p->fd, p->buf, p->i);
		p->i = 0;
	}
	else
		p->buf[p->i++] = *p->format;
	return (1);
}

int			ft_printf(const char *restrict format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			p.c = 0;
			printf_buf(&p, 1);
			if (!parser(&p))
				break ;
		}
		else
			printf_buf(&p, 0);
		++p.format;
	}
	printf_buf(&p, 1);
	va_end(p.ap);
	return (p.len);
}

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			p.c = 0;
			printf_buf(&p, 1);
			if (!parser(&p))
				break ;
		}
		else
			printf_buf(&p, 0);
		++p.format;
	}
	printf_buf(&p, 1);
	va_end(p.ap);
	return (p.len);
}
