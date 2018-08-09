/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 14:10:23 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 18:45:20 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

unsigned int	little_endian(unsigned int i)
{
	i = ((i >> 24) & 0xff) | ((i << 8) & 0xff0000) |
		((i >> 8) & 0xff00) | ((i << 24) & 0xff000000);
	return (i);
}

void			check_header(int i)
{
	if (g_vm->champion[i]->magic != COREWAR_EXEC_MAGIC)
		error_vm("ERROR [HEADER] [MAGIC NUMBER]\n", 0);
	if (!g_vm->champion[i]->name)
		error_vm("ERROR [HEADER] [NAME]\n", 0);
	if (!g_vm->champion[i]->comment)
		error_vm("ERROR [HEADER] [COMMENT]\n", 0);
}

int				read_header(int i)
{
	t_header	*header;
	int			fd;

	if (!(header = malloc(sizeof(t_header))))
		error_vm("malloc failed in read_header\n", 0);
	if ((fd = open(g_vm->champion[i]->filename, O_RDONLY)) == -1 ||
			read(fd, header, sizeof(t_header)) == -1)
		error_vm("open", i);
	if (!(g_vm->champion[i]->name = ft_strdup(header->prog_name)))
		error_vm("malloc failed in read_header\n", 0);
	if (!(g_vm->champion[i]->comment = ft_strdup(header->comment)))
		error_vm("malloc failed in read_header\n", 0);
	g_vm->champion[i]->magic = little_endian(header->magic);
	g_vm->champion[i]->prog_size = little_endian(header->prog_size);
	free(header);
	check_header(i);
	return (fd);
}

int				read_code(int i, int fd)
{
	int			size;
	int			ret;

	ret = 0;
	size = g_vm->champion[i]->prog_size;
	if (!(g_vm->champion[i]->instructions = malloc(size + 1)))
		error_vm("malloc failed in read_code\n", 0);
	return (read(fd, g_vm->champion[i]->instructions, size));
}

int				read_champ(int i)
{
	int			fd;

	fd = read_header(i);
	if (fd == -1)
		return (-1);
	if ((read_code(i, fd)) == -1)
		return (-1);
	return (0);
}
