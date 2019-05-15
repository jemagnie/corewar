/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_exit.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 16:12:52 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:44:27 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	asm_free(t_parser *p)
{
	int		i;
	int		j;

	(p->file) ? free(p->file) : 0;
	if (p->label)
	{
		i = -1;
		while (++i < p->n_label)
			if (p->label[i].name)
				free(p->label[i].name);
		free(p->label);
	}
	if (p->inst && (i = -1))
	{
		while (++i < p->n_inst && (j = -1))
			while (++j < p->inst[i].n_arg)
				if (p->inst[i].arg[j])
				{
					free(p->inst[i].arg[j]);
					p->inst[i].arg[j] = 0;
				}
		free(p->inst);
	}
	(p->name) ? free(p->name) : 0;
	(p->token) ? free_token(p->token) : 0;
}

void	exit_fail(t_parser *p, char *error, char *s)
{
	t_pos	pos;
	char	*str;
	char	*ind;

	if (s)
	{
		pos = get_pos_error(p, s);
		ft_dprintf(2, "\033[1m%s:%d:%d: \033[31merror: \033[39m%s\033[0m\n",
			p->to_open, pos.x, pos.y, error);
		str = s;
		while (*(str - 1) != '\n' && str != p->file)
			--str;
		ind = str;
		while (*str != '\n' && *str)
			ft_putchar_fd(*str++, 2);
		ft_putchar_fd('\n', 2);
		while (ind != s)
			ft_putchar_fd(*ind++ == '\t' ? '\t' : ' ', 2);
		ft_dprintf(2, "\033[32m^\033[0m\n");
	}
	else
		ft_dprintf(2, "\033[1m%s \033[31merror:\033[39m %s\033[0m\n",
			p->to_open ? p->to_open : "", error);
	asm_free(p);
	exit(EXIT_FAILURE);
}

void	exit_usage(void)
{
	ft_printf("./asm [option] file\n"
		"options:\n"
		"	-o [file]	: choose output file name\n"
		"	-d		: disassemble file (printed in stdout)\n"
		"	-h		: printed hexdump from file created\n");
	exit(EXIT_FAILURE);
}

void	exit_errno(t_parser *p, char *error)
{
	perror(error);
	asm_free(p);
	exit(EXIT_FAILURE);
}
