/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi_ptr.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:56:59 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 19:21:19 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_ptr(char **str)
{
	int		neg;
	long	nb;

	neg = 1;
	nb = 0;
	while (**str == ' ' || (**str > 8 && **str < 14))
		(*str)++;
	if (**str == '-' || **str == '+')
		neg = 44 - *(*str)++;
	while (ft_isdigit(**str))
		nb = nb * 10 + *(*str)++ - '0';
	return (neg * nb);
}
