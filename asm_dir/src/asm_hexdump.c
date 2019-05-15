/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_hexdump.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 17:12:28 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 20:09:03 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	asm_usage_hexdump(void)
{
	ft_printf("\n\033[38;5;1mMagic\033[0m\n"
	"\033[38;5;2mName\033[0m\n"
	"\033[38;5;3mSize\033[0m\n"
	"\033[38;5;4mComment\033[0m\n"
	"\033[38;5;5mBinary\033[0m\n\n");
}

void	putbit(const unsigned char *s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (s[i] < 127 && s[i] > 31)
			ft_putchar(s[i]);
		else
			ft_putchar('.');
	}
	ft_putchar('\n');
}

void	asm_hexdump(const unsigned char *addr, unsigned long size)
{
	unsigned long	a;
	unsigned long	i;

	i = 0;
	while (i < size)
	{
		(!(i % 16)) ? ft_printf("%.7x: ", i) : 0;
		if (i < sizeof(int))
			ft_printf("\033[38;5;1m%.2x\033[0m", addr[i]);
		else if (i < sizeof(int) + PROG_NAME_LENGTH + 4)
			ft_printf("\033[38;5;2m%.2x\033[0m", addr[i]);
		else if (i < sizeof(int) + PROG_NAME_LENGTH + 4 + sizeof(int))
			ft_printf("\033[38;5;3m%.2x\033[0m", addr[i]);
		else if (i < sizeof(t_header))
			ft_printf("\033[38;5;4m%.2x\033[0m", addr[i]);
		else
			ft_printf("\033[38;5;5m%.2x\033[0m", addr[i]);
		i % 2 ? ft_putchar(' ') : 0;
		(i % 16) == 15 ? putbit(addr + i - 15, 16) : 0;
		i++;
	}
	a = i - 1;
	while (++a % 16)
		write(1, "   ", a % 2 ? 3 : 2);
	(i % 16) ? putbit(addr + i - i % 16, i % 16) : 0;
}
