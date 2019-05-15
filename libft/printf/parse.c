/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 14:29:24 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:49:14 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

static int	parse_pad(t_printf *p)
{
	p->pad = ft_atoi_ptr(&p->format);
	p->format--;
	p->flag |= F_PAD;
	return (1);
}

static int	parse_pre(t_printf *p)
{
	if (*(p->format + 1) > 48 && *(p->format + 1) < 58)
	{
		++p->format;
		p->pre = ft_atoi_ptr(&p->format);
		--p->format;
	}
	else
		p->pre = 0;
	p->flag |= F_PRE;
	return (1);
}

static int	parse_mod(t_printf *p)
{
	if (*p->format == 'h')
	{
		if (p->flag & M_SHORT)
			p->flag |= (M_CHAR);
		else
			p->flag |= (M_SHORT);
		return (1);
	}
	if (*p->format == 'l' || *p->format == 'j' || *p->format == 'z')
	{
		p->flag |= (M_LONG);
		return (1);
	}
	if (*p->format == 'L')
		return (p->flag |= M_BIGL);
	if (*p->format == '@')
	{
		++p->format;
		p->fd = ft_atoi_ptr(&p->format);
		--p->format;
		return (1);
	}
	return (0);
}

static int	parse_conv(t_printf *p)
{
	char	*chr;
	int		i;

	i = 0;
	chr = "sSpdDUoOuxXcCfbr%";
	while (chr[i])
	{
		if (*p->format == chr[i])
		{
			p->flag |= (1 << i);
			break ;
		}
		++i;
	}
	if (*p->format == 'i')
		p->flag |= C_INT;
	return ((short)p->flag ? 1 : 0);
}

int			parser(t_printf *p)
{
	++p->format;
	ft_bzero(&p->arg, 104);
	while (1)
	{
		if (*p->format == '0')
			p->flag |= (F_ZERO);
		else if (*p->format > 47 && *p->format < 58)
			parse_pad(p);
		else if (*p->format == ' ')
			p->flag |= (F_SPACE);
		else if (*p->format == '.')
			parse_pre(p);
		else if (*p->format == '-')
			p->flag |= (F_MINUS);
		else if (*p->format == '+')
			p->flag |= (F_PLUS);
		else if (*p->format == '#')
			p->flag |= (F_DIEZ);
		else if (!parse_mod(p))
			break ;
		++p->format;
	}
	parse_conv(p);
	return (*p->format ? verifer(p) : 0);
}
