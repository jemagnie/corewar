/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_file.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 15:41:27 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:31:36 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char	*skip_blank_and_comment(char *s)
{
	while (1)
	{
		while (ft_isblank(*s))
			++s;
		if (*s == COMMENT_CHAR)
		{
			while (*s && *s != '\n')
				++s;
		}
		if (*s == '\n')
			s++;
		else
			return (s);
	}
}

t_pos	get_pos_error(t_parser *p, char *error)
{
	int		line;
	int		column;
	t_pos	pos;
	char	*s;

	line = 1;
	column = 1;
	s = p->file;
	while (s != error)
	{
		if (*s == '\n')
		{
			++line;
			column = 1;
		}
		else
			++column;
		++s;
	}
	pos.x = line;
	pos.y = column;
	return (pos);
}
