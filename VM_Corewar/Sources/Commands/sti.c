/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 06:45:11 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_sti(t_process **proc)
{
	int				fparam;
	int				sparam;
	unsigned char	*tab;
	int				aim;
	int				var;

	var = -1;
	fparam = 0;
	sparam = 0;
	if (PROC->params[1][0] == REG_CODE)
		fparam = PROC->reg[PROC->params[1][1]];
	if (PROC->params[1][0] == DIR_CODE)
		fparam = PROC->params[1][1];
	if (PROC->params[1][0] == IND_CODE)
		fparam = read_map(PROC->params[1][1] % IDX_MOD + PROC->begin);
	if (PROC->params[2][0] == REG_CODE)
		sparam = PROC->reg[PROC->params[2][1]];
	if (PROC->params[2][0] == DIR_CODE)
		sparam = PROC->params[2][1];
	if ((aim = (fparam + sparam) % IDX_MOD + PROC->begin) < 0)
		aim += MEM_SIZE;
	tab = itoo(PROC->reg[PROC->params[0][1]]);
	while (++var < 4)
		print(PROC->reg[1], (aim + var) % MEM_SIZE, tab[var]);
	free(tab);
}
