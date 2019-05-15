/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 19:18:51 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 22:59:42 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwchar(wchar_t wc)
{
	int		test;

	if (wc < 0x80)
	{
		test = (int)wc;
		return (write(1, &test, 1));
	}
	if (wc < 0x800)
	{
		test = (((wc & (0x1f << 6)) >> 6) | 0xC0 | (((wc & 0x3f) | 0x80) << 8));
		return (write(1, &test, 2));
	}
	if (wc < 0x10000)
	{
		test = ((((wc & 0x3f) | 0x80) << 16) |
			((((wc >> 6) & 0x3f) | 0x80) << 8) | (((wc >> 12) & 0xf) | 0xE0));
		return (write(1, &test, 3));
	}
	else
	{
		test = ((((wc & 0x3f) | 0x80) << 24) |
			((((wc >> 6) & 0x3f) | 0x80) << 16) |
			((((wc >> 12) & 0x3f) | 0x80) << 8) | (((wc >> 18) & 7) | 0xF0));
		return (write(1, &test, 4));
	}
}
