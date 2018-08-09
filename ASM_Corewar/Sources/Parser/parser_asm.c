/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_asm.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 22:48:37 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 22:48:37 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		cmd_is_good(char *cmd)
{
	if (cmd[0] == CHAR_CMD &&
		ft_strcmp(cmd, CMD_NAME) && ft_strcmp(cmd, CMD_COMMENT))
		return (1);
	if ((ft_count_chars(cmd, CHAR_NEGATIVE)) > 1)
		return (1);
	if (!(ft_strcmp(cmd, "%")))
		return (1);
	if (!(ft_strcmp(cmd, ":")))
		return (1);
	if (!(ft_strcmp(cmd, "-")))
		return (1);
	return (0);
}

int		add_cmd(t_cmd **result, t_pos *pos, char *buf, int fd)
{
	t_cmd	*previous;
	int		string;

	string = (*buf == CHAR_STRING) ? 1 : 0;
	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : (*result);
	(*result) = ft_memalloc(sizeof(t_cmd));
	(*result)->pos = (*pos);
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	(*buf) = parser_elem(pos, &((*result)->data), (*buf), fd);
	if ((*buf) != CHAR_STRING && cmd_is_good((*result)->data))
		return (0);
	if (!((*result)->token))
		(*result)->token = token_dispenser((*result)->data, buf, string);
	if ((*result)->token == STRING)
		read(fd, buf, 1);
	return (1);
}

int		add_line(t_line **result, t_pos *pos, char *buf, int fd)
{
	t_line		*previous;
	int			ret;

	ret = add_cmd(&((*result)->line), pos, buf, fd);
	(*pos) = init_pos((pos->y + 1), 1);
	if (!((*result)->line))
		return (ret);
	else
		(*result)->line = (*result)->line->start;
	(*result)->size = (*result)->start->size;
	(*result)->line->octet = parser_instruction(*result, (*result)->line);
	(*result)->start->size += (*result)->line->octet;
	if ((*result)->start->size > CHAMP_MAX_SIZE)
		print_error_size_code(*result);
	previous = (*result);
	(*result) = (*result)->next;
	(*result) = ft_memalloc(sizeof(t_line));
	(*result)->prev = previous;
	previous->next = (*result);
	(*result)->start = previous->start;
	return (ret);
}

t_line	*parser(t_line *result, int fd)
{
	t_pos	pos;
	char	buf;
	int		ret;

	init_parser(&result, &pos, &buf, &ret);
	while ((ret = special_read(&pos, &buf, ret, fd)))
	{
		if ((!(ft_strchr(CHARS_VALID, buf)) && !(ft_iscntrl(buf))))
			print_error_lexical(result, pos);
		else if (buf == CHAR_COMMENT)
			ret = pass_comment(result->line, &buf, fd);
		else if (buf == CHAR_LINE)
			ret = add_line(&result, &pos, &buf, fd);
		else if (ft_strchr(CHARS_VALID, buf))
			if (!(add_cmd(&(result->line), &pos, &buf, fd)))
				print_error_lexical(result, result->line->pos);
	}
	add_cmd(&(result->line), &pos, (char *)&ret, fd);
	return (result->start);
}
