/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 18:17:19 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 00:24:34 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwstr(wchar_t *s)
{
	int		len;

	len = 0;
	while (*s != L'\0')
	{
		len += ft_putwchar(*s);
		++s;
	}
	return (len);
}

int		ft_putnwstr(wchar_t *s, int n)
{
	int		len;

	len = 0;
	while (*s != L'\0')
	{
		if ((n -= ft_wclen(*s)) < 0)
			break ;
		len += ft_putwchar(*s);
		++s;
	}
	return (len);
}
