/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_bits.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/30 22:23:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:31:22 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		reverse_int_bits(int bin)
{
	int		bin1;
	int		bin2;
	int		bin3;
	int		bin4;

	bin1 = (bin & 0xFF) << 24;
	bin2 = (bin & 0xFF00) << 8;
	bin3 = (bin & 0xFF0000) >> 8;
	bin4 = (bin & 0xFF000000) >> 24;
	return (bin1 | bin2 | bin3 | bin4);
}

short	reverse_short_bits(short bin)
{
	return (((bin & 0xFF) << 8) | ((bin & 0xFF00) >> 8));
}
