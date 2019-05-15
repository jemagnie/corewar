/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_opc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 01:09:37 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 16:32:06 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	get_asm_ocp(t_parser *p, t_inst *inst)
{
	int		i;
	char	ocp;
	int		mv;

	i = 0;
	mv = 6;
	ocp = 0;
	(void)p;
	while (i < inst->n_arg)
	{
		ocp |= inst->code[i] << mv;
		mv -= 2;
		++i;
	}
	inst->ocp = ocp;
}
