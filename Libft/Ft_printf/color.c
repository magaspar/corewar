/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/29 14:00:54 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 14:00:03 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_checkcolor(char *str)
{
	if (ft_strncmp(str, "{red}", 5) == 0)
		return (ft_strdup("\033[31m"));
	else if (ft_strncmp(str, "{black}", 7) == 0)
		return (ft_strdup("\033[30m"));
	else if (ft_strncmp(str, "{blue}", 6) == 0)
		return (ft_strdup("\033[34m"));
	else if (ft_strncmp(str, "{white}", 7) == 0)
		return (ft_strdup("\033[37m"));
	else if (ft_strncmp(str, "{cyan}", 6) == 0)
		return (ft_strdup("\033[36m"));
	else if (ft_strncmp(str, "{yellow}", 8) == 0)
		return (ft_strdup("\033[33m"));
	else if (ft_strncmp(str, "{magenta}", 9) == 0)
		return (ft_strdup("\033[35m"));
	else if (ft_strncmp(str, "{green}", 7) == 0)
		return (ft_strdup("\033[32m"));
	else if (ft_strncmp(str, "{n_white}", 7) == 0)
		return (ft_strdup("\033[47m"));
	return (NULL);
}

static char		*ft_strreplace1(char *dst, char *src, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(dst) - (end - start) + ft_strlen(src);
	if (!(ret = malloc(sizeof(char) * i + 2)))
		return (NULL);
	i = 0;
	while (i < start)
	{
		ret[i] = dst[i];
		i++;
	}
	while (src[j])
		ret[i++] = src[j++];
	while (dst[++end])
		ret[i++] = dst[end];
	ret[i] = '\0';
	ft_strdel(&dst);
	return (ret);
}

static char		*ft_strreplace3(char *dst, char *src, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(dst) - (end - start) + ft_strlen(src);
	if (!(ret = malloc(sizeof(char) * i + 2)))
		return (NULL);
	i = 0;
	while (i < start)
	{
		ret[i] = dst[i];
		i++;
	}
	while (src[j])
		ret[i++] = src[j++];
	while (dst[++end])
		ret[i++] = dst[end];
	ret[i] = '\0';
	ft_strdel(&dst);
	ft_strdel(&src);
	return (ret);
}

int				ft_colorlen(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '{')
		{
			if (ft_checkcolor(str + i) != NULL)
				j++;
		}
		i++;
	}
	return (j * 8);
}

char			*ft_color(char *str)
{
	int		i;
	int		j;
	char	*code;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = 0;
			if ((code = ft_checkcolor(str + i)) != NULL)
			{
				while (str[i + j] != '}')
					j++;
				str = ft_strreplace3(str, code, i, i + j);
			}
			else if (ft_strncmp(str + i, "{eoc}", 5) == 0)
			{
				str = ft_strreplace1(str, "\033[m", i, i + 4);
			}
		}
		i++;
	}
	return (str);
}
