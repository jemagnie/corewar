/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_inst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/31 15:48:12 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 17:09:01 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_op_tab	g_asm_tab[17] =
{
	{"live", 1, 1, {T_DIR}, 0, 0},
	{"lldi", 14, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 1},
	{"lld", 13, 2, {T_DIR | T_IND, T_REG}, 1, 0},
	{"ldi", 10, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 1},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 0},
	{"sti", 11, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 1},
	{"st", 3, 2, {T_REG, T_IND | T_REG}, 1, 0},
	{"add", 4, 3, {T_REG, T_REG, T_REG}, 1, 0},
	{"sub", 5, 3, {T_REG, T_REG, T_REG}, 1, 0},
	{"and", 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"or", 7, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"xor", 8, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"zjmp", 9, 1, {T_DIR}, 0, 1},
	{"fork", 12, 1, {T_DIR}, 0, 1},
	{"lfork", 15, 1, {T_DIR}, 0, 1},
	{"aff", 16, 1, {T_REG}, 1, 0},
	{0, 0, 0, {0}, 0, 0}
};

void	asm_fill_param(t_parser *p, char *s, int index, int arg)
{
	if (*s == DIRECT_CHAR)
	{
		if (!(g_asm_tab[index].arg[arg] & T_DIR))
			exit_fail(p, "invalid param type", p->inst[p->n_inst++].tmp[arg]);
		p->inst[p->n_inst].len[arg] = g_asm_tab[index].dir_size ? 2 : 4;
		p->inst[p->n_inst].code[arg] = DIR_CODE;
	}
	else if (*s == REG_CHAR)
	{
		if (!(g_asm_tab[index].arg[arg] & T_REG))
			exit_fail(p, "invalid param type", p->inst[p->n_inst++].tmp[arg]);
		p->inst[p->n_inst].len[arg] = 1;
		p->inst[p->n_inst].code[arg] = REG_CODE;
	}
	else
	{
		if (!(g_asm_tab[index].arg[arg] & T_IND))
			exit_fail(p, "invalid param type", p->inst[p->n_inst++].tmp[arg]);
		p->inst[p->n_inst].len[arg] = 2;
		p->inst[p->n_inst].code[arg] = IND_CODE;
	}
	p->inst[p->n_inst].total += p->inst[p->n_inst].len[arg];
}

void	asm_get_param(t_parser *p, char *s, int n_arg, int index)
{
	int		i;
	int		j;

	i = -1;
	while (++i < n_arg && !(j = 0))
	{
		while (ft_isblank(*s))
			++s;
		p->inst[p->n_inst].tmp[i] = s;
		if ((*s == SEPARATOR_CHAR || *s == COMMENT_CHAR || *s == '\n'
			|| !*s) && ++p->n_inst)
			exit_fail(p, "last param empty", s);
		while (s[j] != COMMENT_CHAR && s[j] != SEP_CHAR && s[j] != '\n' && s[j])
			++j;
		if (!(p->inst[p->n_inst].arg[i] = ft_strnepur(s, j)))
			exit_errno(p, "Malloc failed");
		asm_fill_param(p, p->inst[p->n_inst].arg[i], index, i);
		s = s + j + (s[j] == SEPARATOR_CHAR);
	}
	if (*s != '\n' && *s != COMMENT_CHAR && *s)
	{
		p->n_inst++;
		exit_fail(p, "invalid token", s);
	}
	p->offset = s;
}

void	get_asm_inst(t_parser *p, char *s, int index)
{
	if (!p->inst)
	{
		if (!(p->inst = ft_memalloc(sizeof(t_inst))))
			exit_errno(p, "Malloc failed");
	}
	else if (!(p->inst = realloc(p->inst, sizeof(t_inst) * (p->n_inst + 1))))
		exit_errno(p, "Realloc failed");
	ft_bzero(&(p->inst[p->n_inst]), sizeof(t_inst));
	p->inst[p->n_inst].opcode = g_asm_tab[index].opcode;
	p->inst[p->n_inst].n_arg = g_asm_tab[index].n_arg;
	asm_get_param(p, s, g_asm_tab[index].n_arg, index);
	p->inst[p->n_inst].total += 1;
	if (g_asm_tab[index].opc)
	{
		get_asm_ocp(p, &(p->inst[p->n_inst]));
		p->inst[p->n_inst].total += 1;
	}
	p->inst[p->n_inst].addr = p->len_mem;
	p->len_mem += p->inst[p->n_inst].total;
	++(p->n_inst);
}

int		asm_is_inst(t_parser *p, char *s)
{
	int		i;
	int		count;
	char	*str;

	i = -1;
	while (g_asm_tab[++i].name)
		if (!ft_strncmp(g_asm_tab[i].name, s, ft_strlen(g_asm_tab[i].name)))
			break ;
	if (i == INST_NUMBER)
		exit_fail(p, "invalid instruction", p->offset);
	s += ft_strlen(g_asm_tab[i].name);
	s = ft_strwhile(s, ft_isblank);
	count = (*s != '\n' && *s != COMMENT_CHAR && *s) ? 1 : 0;
	p->offset = s;
	str = s;
	while (*s != '\n' && *s != COMMENT_CHAR && *s)
		if (*s++ == SEPARATOR_CHAR)
		{
			str = s;
			++count;
		}
	if (count != g_asm_tab[i].n_arg)
		exit_fail(p, "invalid number of parameter for instruction", str);
	return (i);
}
