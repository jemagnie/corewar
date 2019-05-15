/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_token.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 16:38:05 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:32:46 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	free_token(t_oken *token)
{
	t_oken	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->s)
			free(token->s);
		free(token);
		token = tmp;
	}
}

void	new_token(t_parser *p, char *s, int type, char *err)
{
	t_oken	*new;

	if (!s)
		exit_errno(p, "Malloc failed");
	if (!(new = ft_memalloc(sizeof(t_oken))))
	{
		free(s);
		exit_errno(p, "Malloc failed");
	}
	new->s = s;
	new->type = type;
	new->err = err;
	type & IS_NB ? new->nb = ft_atoi(s) : 0;
	if (type & IS_OP)
		new->predecence = *s == '+' || *s == '-' ? 1 : 2;
	new->next = p->token;
	p->token = new;
}

void	asm_get_token(t_parser *p, char *s, char *err)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')')
			new_token(p, ft_strndup(s + i, 1), s[i] == '(' ?
				IS_LEFT_PAR : IS_RIGHT_PAR, err + i);
		else if (s[i] == '*' || s[i] == '+' || s[i] == '/' || s[i] == '%' ||
			(s[i] == '-' && p->token &&
			(p->token->type & IS_NB || *(p->token->s) == ')')))
			new_token(p, ft_strndup(s + i, 1), IS_OP, err + i);
		else if (ft_isnumber(s + i))
		{
			new_token(p, ft_strndup(s + i, ft_isnumber(s + i)), IS_NB, err + i);
			i += ft_isnumber(s + i) - 1;
		}
		else if (!ft_isblank(s[i]))
			exit_fail(p, "Invalid token for calcul", err + i);
		++i;
	}
}

void	ft_tokenrev(t_oken **token)
{
	t_oken	*first;
	t_oken	*mid;
	t_oken	*last;

	if (!((*token)->next))
		return ;
	first = *token;
	mid = first->next;
	last = first->next->next;
	first->next = NULL;
	mid->next = first;
	while (last)
	{
		first = mid;
		mid = last;
		last = last->next;
		mid->next = first;
	}
	*token = mid;
}

int		check_token_calc(t_parser *p, t_oken *token, int stack)
{
	while (token)
	{
		if ((token->next && (token->next->type == token->type) &&
			!(token->type & (IS_LEFT_PAR | IS_RIGHT_PAR))) ||
			((token->type & IS_OP && (!token->next ||
			(token->next->type & IS_RIGHT_PAR))) || (token->type & IS_NB
			&& token->next && token->next->type & IS_LEFT_PAR)))
			exit_fail(p, "invalid syntax expression", token->next ?
				token->next->err : token->err);
		if (token->type & IS_LEFT_PAR)
		{
			if (token->next && (token->next->type & (IS_RIGHT_PAR | IS_OP)))
				exit_fail(p, "invalid syntax parenthese", token->err);
			++stack;
		}
		if (token->type & IS_RIGHT_PAR)
		{
			--stack;
			if (stack < 0 || (token->next &&
				!(token->next->type & (IS_OP | IS_RIGHT_PAR))))
				exit_fail(p, "invalid syntax parenthese", token->err);
		}
		token = token->next;
	}
	return ((stack == 0));
}
