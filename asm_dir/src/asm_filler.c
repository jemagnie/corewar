/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_filler.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 15:53:42 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:59:45 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	get_param_char(t_parser *p, t_inst inst, char *mem, int arg)
{
	char	*s;
	int		c;

	s = inst.arg[arg];
	c = asm_get_calc(p, s + 1, inst.tmp[arg] + 1);
	if (c < 1 || c > REG_NUMBER)
		exit_fail(p, "invalid register param (r1 <=> r16)", inst.tmp[arg]);
	*mem = (char)c;
}

void	get_param_short(t_parser *p, t_inst inst, short *mem, int arg)
{
	char	*s;
	int		i;
	int		c;

	s = inst.arg[arg] + (*(inst.arg[arg]) == DIRECT_CHAR);
	i = -1;
	if (!*s)
		exit_fail(p, "invalid param, empty", inst.tmp[arg]);
	if (*s == LABEL_CHAR)
	{
		++s;
		if ((c = get_addr_label(p, p->label, s)) == -1)
			exit_fail(p, "invalid param, label doest not exist", inst.tmp[arg]);
		c = c - inst.addr;
	}
	else
	{
		c = asm_get_calc(p, s, inst.tmp[arg]);
	}
	*mem = reverse_short_bits((short)c);
}

void	get_param_int(t_parser *p, t_inst inst, int *mem, int arg)
{
	char	*s;
	int		c;

	s = inst.arg[arg] + 1;
	if (!*s)
		exit_fail(p, "invalid param, empty", inst.tmp[arg]);
	if (*s == LABEL_CHAR)
	{
		if ((c = get_addr_label(p, p->label, ++s)) == -1)
			exit_fail(p, "invalid direct, label does not exist",
				inst.tmp[arg] + 2);
		c = c - inst.addr;
	}
	else
	{
		c = asm_get_calc(p, s, inst.tmp[arg] + 1);
	}
	*mem = reverse_int_bits(c);
}

void	asm_writer(t_parser *p)
{
	int		len;
	char	*name;

	if (p->name)
		name = ft_strdup(p->name);
	else
	{
		len = ft_strlen(p->to_open) - 2;
		if (!(name = ft_strnew(sizeof(char) * (len + 4))))
			exit_errno(p, "Malloc failed");
		ft_strncpy(name, p->name ? p->name : p->to_open, len);
		ft_strcat(name, ".cor");
	}
	if ((p->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		exit_errno(p, "Open failed");
	p->head.prog_size = reverse_int_bits(p->len_mem);
	write(p->fd, &(p->head), sizeof(t_header) + p->len_mem);
	ft_printf("[%s] created\n", name);
	if (p->flag & HEXDUMP_OPTION)
	{
		asm_usage_hexdump();
		asm_hexdump((unsigned char *)(&(p->head)),
			sizeof(t_header) + p->len_mem);
	}
	free(name);
}

void	asm_filler(t_parser *p, t_inst *inst, char *mem)
{
	int		i;
	int		j;

	i = -1;
	while (++i < p->n_inst)
	{
		j = -1;
		*mem++ = inst[i].opcode;
		if (inst[i].ocp)
			*mem++ = inst[i].ocp;
		while (++j < inst[i].n_arg)
		{
			if (inst[i].len[j] == 4)
				get_param_int(p, inst[i], (int *)mem, j);
			else if (inst[i].len[j] == 2)
				get_param_short(p, inst[i], (short *)mem, j);
			else
				get_param_char(p, inst[i], mem, j);
			mem += inst[i].len[j];
		}
	}
	asm_writer(p);
	asm_free(p);
}
