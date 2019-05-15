/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 18:17:59 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 00:52:27 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(wchar_t *s)
{
	size_t	len;

	len = 0;
	while (*s != L'\0')
	{
		len += ft_wclen(*s);
		++s;
	}
	return (len);
}

size_t	ft_nwstrlen(wchar_t *s, int n)
{
	size_t	len;
	int		tmp;

	len = 0;
	while (*s != L'\0')
	{
		tmp = ft_wclen(*s);
		if ((n -= tmp) < 0)
			break ;
		len += tmp;
		++s;
	}
	return (len);
}
