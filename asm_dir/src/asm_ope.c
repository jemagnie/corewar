/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_ope.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 20:34:53 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:59:54 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	push_to_op(t_oken **token, t_oken **op)
{
	(*token)->ope = *op;
	*op = *token;
}

void	push_to_out(t_oken **token, t_oken **out, int loop)
{
	(*token)->out = *out;
	*out = *token;
	if (loop)
		*token = (*token)->ope;
}

void	do_calcul(t_parser *p, t_oken *token, t_oken *out, char *err)
{
	if (out->out)
		do_calcul(p, token, out->out, err);
	if (out->type & IS_OP)
		if (out->out && out->out->out &&
			out->out->type & IS_NB && out->out->out->type & IS_NB)
		{
			if (*out->s == '+')
				out->nb = out->out->out->nb + out->out->nb;
			if (*out->s == '-')
				out->nb = out->out->out->nb - out->out->nb;
			if (*out->s == '*')
				out->nb = out->out->out->nb * out->out->nb;
			if ((*out->s == '/' || *out->s == '%') && out->out->nb == 0)
				exit_fail(p, "div by zero", out->err);
			if (*out->s == '/')
				out->nb = out->out->out->nb / out->out->nb;
			if (*out->s == '%')
				out->nb = out->out->out->nb % out->out->nb;
			out->type = IS_NB;
			out->out = out->out->out->out;
		}
}

t_oken	*shunting_yard(t_oken *token, t_oken *op, t_oken *out)
{
	while (token)
	{
		if (token->type & IS_NB)
			push_to_out(&token, &out, 0);
		else if (token->type & IS_OP)
		{
			while (op && op->predecence && op->predecence >= token->predecence)
				push_to_out(&op, &out, 1);
			push_to_op(&token, &op);
		}
		else if (token->type & IS_LEFT_PAR)
			push_to_op(&token, &op);
		else
		{
			while (op && !(op->type & IS_LEFT_PAR))
				push_to_out(&op, &out, 1);
			op = op->ope;
		}
		token = token->next;
	}
	while (op)
		push_to_out(&op, &out, 1);
	return (out);
}

int		asm_get_calc(t_parser *p, char *s, char *err)
{
	t_oken		*out;
	int			res;

	if ((size_t)ft_isnumber(s) == ft_strlen(s))
		return (ft_atoi(s));
	else if (*s == '(' && *(s + ft_strlen(s) - 1) == ')')
	{
		asm_get_token(p, s, err);
		if (!p->token)
			exit_fail(p, "invalid expression arithmetic", err);
		ft_tokenrev(&(p->token));
		if (!check_token_calc(p, p->token, 0))
			exit_fail(p, "invalid expression arithmetic", err);
		out = shunting_yard(p->token, NULL, NULL);
		do_calcul(p, p->token, out, err);
		res = out->nb;
		free_token(p->token);
		p->token = NULL;
		return (res);
	}
	else
		exit_fail(p, "invalid param", err);
	return (1);
}
