/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:46:57 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:21:08 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		print(int player, int index, int value)
{
	g_vm->map[index] = value;
	g_vm->p_map[index] = player;
}

void		norme_remove(t_process **list)
{
	(*list)->live = 0;
	(*list) = (*list)->next;
}

int			check_data(void)
{
	unsigned int i;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		if (g_vm->champion[i]->prog_size > MEM_SIZE / 6)
			error_vm("size", i);
	}
	return (0);
}

void		introduction(void)
{
	int i;

	i = g_vm->nb_players - 1;
	ft_printf("Introducing contestants...\n");
	while (i >= 0)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				(g_vm->champion[i]->num >= 0 ? g_vm->champion[i]->num :
				g_vm->champion[i]->num * -1),
				g_vm->champion[i]->prog_size,
				g_vm->champion[i]->name,
				g_vm->champion[i]->comment);
		i--;
	}
}

void		process_remove_if_live(t_process **begin_list)
{
	t_process	*list;
	t_process	*tmp;

	list = *begin_list;
	while (list)
	{
		if (list == *begin_list && list->live == 0)
		{
			*begin_list = (*begin_list)->next;
			free_process(list);
			list = *begin_list;
		}
		else if (list->next && list->next->live == 0)
		{
			tmp = list->next->next;
			free_process(list->next);
			list->next = tmp;
		}
		else
			norme_remove(&list);
	}
}
