/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_label.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/31 01:17:25 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:31:58 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		asm_label_exist(t_parser *p, char *s, int len)
{
	int		i;
	int		n;

	i = 0;
	n = p->n_label;
	(void)len;
	while (i < n)
	{
		if (!ft_strcmp(p->label[i].name, s))
			return (0);
		++i;
	}
	return (1);
}

int		get_addr_label(t_parser *p, t_label *label, char *s)
{
	int		i;
	int		n;

	i = 0;
	n = p->n_label;
	while (i < n)
	{
		if (!ft_strcmp(label[i].name, s))
		{
			return (label[i].addr);
		}
		++i;
	}
	return (-1);
}

void	get_asm_label(t_parser *p, char *s)
{
	int		i;
	char	*new;

	i = 0;
	while (s[i] != LABEL_CHAR)
		++i;
	if (!p->label)
	{
		if (!(p->label = malloc(sizeof(t_label) * (p->n_label + 1))))
			exit_errno(p, "Malloc failed");
	}
	else if (!(p->label = realloc(p->label,
		sizeof(t_label) * (p->n_label + 1))))
		exit_errno(p, "Realloc failed");
	if (!(new = ft_strndup(s, i)))
		exit_errno(p, "Malloc failed");
	if (!asm_label_exist(p, new, i))
		exit_fail(p, "Label already exist", s);
	p->label[p->n_label].name = new;
	p->label[p->n_label].addr = p->len_mem;
	p->offset = s + i + 1;
	p->offset = skip_blank_and_comment(p->offset);
	++(p->n_label);
}

int		asm_is_label(t_parser *p, char *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != LABEL_CHAR && s[i] != COMMENT_CHAR
		&& !(ft_isblank(s[i])))
		i++;
	if (!s[i] || s[i] == '\n' || s[i] == COMMENT_CHAR || ft_isblank(s[i]))
		return (0);
	i = 0;
	while (ft_strchr(LABEL_CHARS, s[i]))
		++i;
	if (s[i] != LABEL_CHAR)
	{
		j = -1;
		while (g_asm_tab[++j].name)
			if (!ft_strncmp(g_asm_tab[j].name, s, ft_strlen(g_asm_tab[j].name)))
				break ;
		if (j < INST_NUMBER && s[i] && s[i + 1] == LABEL_CHAR)
			return (0);
		exit_fail(p, "Invalid character for label", s + i);
	}
	if (i == 0)
		exit_fail(p, "Label is empty", s + i);
	return (1);
}
