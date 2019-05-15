/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 19:04:16 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:49:21 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

int		long_len(t_printf p, const long n)
{
	long	value;
	int		i;

	i = 0;
	value = n < 0 ? -n : n;
	if (!n)
	{
		if (p.flag & F_PRE)
			if (p.pre == 0)
				return (0);
		return (1);
	}
	while (value)
	{
		i++;
		value /= 10;
	}
	return (i);
}

int		ulong_base_len(t_printf p, unsigned long n, const int base)
{
	int		i;

	i = 0;
	if (!n)
	{
		if (p.flag & F_PRE)
			if (p.pre == 0)
				return (0);
		return (1);
	}
	(void)p;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}
