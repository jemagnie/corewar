/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_des.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 18:52:47 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:31:27 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	asm_print_short(t_parser *p)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = p->offset;
	while (++i < 2)
	{
		p->offset++;
		if (p->offset - p->file > p->len_file)
			exit_fail(p, "Invalid binary", 0);
	}
	ft_printf("%%%hd", reverse_short_bits(*(short *)(tmp)));
}

void	asm_print_int(t_parser *p)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = p->offset;
	while (++i < 4)
	{
		p->offset++;
		if (p->offset - p->file > p->len_file)
			exit_fail(p, "Invalid binary", 0);
	}
	ft_printf("%%%d", reverse_int_bits(*(int *)(tmp)));
}

void	asm_print_short_ind(t_parser *p)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = p->offset;
	while (++i < 2)
	{
		p->offset++;
		if (p->offset - p->file > p->len_file)
			exit_fail(p, "Invalid binary", 0);
	}
	ft_printf("%hd", reverse_short_bits(*(short *)(tmp)));
}

void	asm_print_ocp(t_parser *p, int index)
{
	int		i;
	int		mov;
	int		ocp;

	i = -1;
	ocp = *(p->offset++);
	mov = 6;
	while (++i < g_asm_tab[index].n_arg)
	{
		if (((ocp >> mov) & 0x3) == 3)
			asm_print_short_ind(p);
		else if (((ocp >> mov) & 0x3) == 1)
			ft_printf("r%hhd", *(p->offset++));
		else if (((ocp >> mov) & 0x3) == 2)
		{
			if (g_asm_tab[index].dir_size)
				asm_print_short(p);
			else
				asm_print_int(p);
		}
		if (i + 1 != g_asm_tab[index].n_arg)
			ft_printf(", ");
		mov -= 2;
	}
}

void	asm_reverse(t_parser *p)
{
	int		i;

	while (*p->offset > 0 && *p->offset < 17)
	{
		i = 0;
		while (g_asm_tab[i].opcode != *p->offset)
			++i;
		ft_printf("%s\t", g_asm_tab[i].name);
		p->offset++;
		if (g_asm_tab[i].opc)
			asm_print_ocp(p, i);
		else
		{
			if (g_asm_tab[i].dir_size)
				asm_print_short(p);
			else
				asm_print_int(p);
		}
		ft_printf("\n");
	}
	if (p->offset != p->file + p->len_file)
		exit_fail(p, "Invalid binary", 0);
	asm_free(p);
}
