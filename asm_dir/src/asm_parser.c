/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 17:45:22 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:32:15 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*valid_cmd_comment(t_parser *p, char *s)
{
	s = skip_blank_and_comment(s);
	if (!*s)
		exit_fail(p, "missing comment command", s);
	s = ft_strwhile(s, ft_isblank);
	if (ft_strncmp(s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		exit_fail(p, "invalid command", s);
	s += ft_strlen(COMMENT_CMD_STRING);
	return (s);
}

static void		get_str_comment(t_parser *p, char *s)
{
	int		i;

	i = 0;
	s = valid_cmd_comment(p, s);
	s = ft_strwhile(s, ft_isblank);
	if (*s++ != 34)
		exit_fail(p, "invalid string comment, missing quote mark", s - 1);
	while (s[i] != 34 && s[i])
		++i;
	if (s[i] == 0)
		exit_fail(p, "invalid string comment, missing quote mark", s + i);
	if (i > COMMENT_LENGTH)
		exit_fail(p, "invalid string comment, too long", s);
	ft_memcpy(p->head.comment, s, i);
	s = ft_strwhile(s + i + 1, ft_isblank);
	if (*s == COMMENT_CHAR)
		while (*s != '\n')
			++s;
	if (!*s || *s != '\n')
		exit_fail(p, "missing newline before instruction", s);
	p->offset = s;
}

static char		*valid_cmd_name(t_parser *p, char *s)
{
	s = skip_blank_and_comment(s);
	if (!*s)
		exit_fail(p, "missing name command", s);
	s = ft_strwhile(s, ft_isblank);
	if (ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		exit_fail(p, "invalid name command", s);
	s += ft_strlen(NAME_CMD_STRING);
	return (s);
}

static void		get_str_name(t_parser *p, char *s)
{
	int		i;

	i = 0;
	s = valid_cmd_name(p, s);
	s = ft_strwhile(s, ft_isblank);
	if (*s++ != 34)
		exit_fail(p, "invalid string name, missing quote mark", s - 1);
	while (s[i] != 34 && s[i])
		++i;
	if (i > PROG_NAME_LENGTH)
		exit_fail(p, "invalid string name, too long", s);
	if (!s[i])
		exit_fail(p, "invalid string name, missing quotation mark", s + i);
	ft_memcpy(p->head.prog_name, s, i);
	s = ft_strwhile(s + i + 1, ft_isblank);
	if (*s == COMMENT_CHAR)
		while (*s != '\n' && *s)
			++s;
	if (!*s || *s != '\n')
		exit_fail(p, "missing newline before comment command", s);
	p->offset = s;
}

void			asm_parser(t_parser *p)
{
	int		inst;

	p->offset = p->file;
	get_str_name(p, p->offset);
	get_str_comment(p, p->offset);
	p->head.magic = reverse_int_bits(COREWAR_EXEC_MAGIC);
	while (*(p->offset))
	{
		p->offset = skip_blank_and_comment(p->offset);
		if (asm_is_label(p, p->offset))
		{
			get_asm_label(p, p->offset);
			continue ;
		}
		if (!*p->offset)
			continue ;
		if ((inst = asm_is_inst(p, p->offset)) != -1)
			get_asm_inst(p, p->offset, inst);
	}
	if (p->len_mem > CHAMP_MAX_SIZE)
		exit_fail(p, "champ too long", 0);
	if (!p->len_mem)
		exit_fail(p, "champ empty", 0);
}
