/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 17:47:44 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 17:47:44 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	free_label(t_label *lab)
{
	t_label		*ptr;

	lab = (lab) ? lab->start : NULL;
	while (lab)
	{
		ptr = lab;
		free(lab->name);
		lab = lab->next;
		ft_memdel((void **)&ptr);
	}
}

void	free_line(t_cmd *line)
{
	t_cmd	*ptr;

	line = (line) ? line->start : NULL;
	while (line)
	{
		ptr = line;
		free(line->data);
		line = line->next;
		ft_memdel((void **)&ptr);
	}
}

void	free_file(t_line *file)
{
	t_line	*ptr;

	if ((file = (file) ? file->start : NULL))
		free_label(file->label);
	while (file)
	{
		ptr = file;
		free_line(file->line);
		file = file->next;
		ft_memdel((void **)&ptr);
	}
}
