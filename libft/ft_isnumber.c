/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isnumber.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 16:28:19 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:28:50 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnumber(const char *s)
{
	int		i;

	i = 0;
	if (s[i] == '-')
		++i;
	if (ft_isdigit(s[i]))
	{
		while (ft_isdigit(s[i]))
			++i;
		return (i);
	}
	return (0);
}
