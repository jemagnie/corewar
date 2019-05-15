/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_main.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 15:19:27 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:50:07 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	asm_desassembler(t_parser *p)
{
	p->offset = p->file;
	ft_memcpy(&p->head, p->offset, sizeof(t_header));
	p->head.magic = reverse_int_bits(p->head.magic);
	p->head.prog_size = reverse_int_bits(p->head.prog_size);
	if (p->len_file - sizeof(t_header) != p->head.prog_size)
		exit_fail(p, "Invalid binary : diff program size", 0);
	if (p->head.magic != COREWAR_EXEC_MAGIC)
		exit_fail(p, "Invalid binary : wrong magic number", 0);
	ft_printf(".name \"%s\"\n", p->head.prog_name);
	ft_printf(".comment \"%s\"\n\n", p->head.comment);
	p->offset += sizeof(t_header);
	asm_reverse(p);
}

void	get_option(t_parser *p, int ac, char **av)
{
	int		i;

	i = 0;
	ft_bzero(p, sizeof(t_parser));
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-o"))
		{
			if (i + 1 == ac)
				exit_fail(p, "argument to '-o' "
					"is missing (expected 1 value)", 0);
			if (p->name)
				free(p->name);
			p->name = ft_strdup(av[++i]);
			p->flag |= OUTPUT_OPTION;
		}
		else if (!ft_strcmp(av[i], "-d"))
			p->flag |= DISSAMBLER_OPTION;
		else if (!ft_strcmp(av[i], "-h"))
			p->flag |= HEXDUMP_OPTION;
		else if (*av[i] == '-')
			exit_fail(p, "invalid option", 0);
	}
	if ((p->flag & DISSAMBLER_OPTION) && (p->flag & HEXDUMP_OPTION))
		exit_fail(p, "incompatible options", 0);
}

void	get_param(t_parser *p, int ac, char **av)
{
	int		i;

	if (p->flag & 1)
		p->suffix = ".cor";
	else
		p->suffix = ".s";
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-o"))
			i++;
		else if (!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-h"))
			continue ;
		else if (!ft_strcmp(av[i] +
			ft_strlen(av[i]) - ft_strlen(p->suffix), p->suffix))
		{
			if (p->to_open)
				exit_fail(p, "too many files", 0);
			p->to_open = av[i];
		}
		else
			exit_fail(p, "invalid file", 0);
	}
	if (!p->to_open)
		exit_fail(p, "missing file to open", 0);
}

int		main(int ac, char **av)
{
	t_parser	p;

	if (ac < 2)
		exit_usage();
	get_option(&p, ac, av);
	get_param(&p, ac, av);
	if ((p.fd = open(p.to_open, O_RDONLY)) == -1)
		exit_errno(&p, "Open failed");
	if ((p.len_file = lseek(p.fd, 0, SEEK_END)) == -1)
		exit_errno(&p, "Lseek failed");
	if (!(p.file = ft_memalloc(sizeof(char) * p.len_file + 1)))
		exit_errno(&p, "Malloc failed");
	if (lseek(p.fd, 0, SEEK_SET) == -1)
		exit_errno(&p, "Lseek failed");
	if (read(p.fd, p.file, p.len_file) == -1)
		exit_errno(&p, "Read failed");
	if (close(p.fd) == -1)
		exit_errno(&p, "Close failed");
	if (p.flag & DISSAMBLER_OPTION)
		asm_desassembler(&p);
	else
	{
		asm_parser(&p);
		asm_filler(&p, p.inst, p.mem);
	}
}
