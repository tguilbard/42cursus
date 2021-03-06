/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:21:19 by tguilbar          #+#    #+#             */
/*   Updated: 2019/11/29 10:30:29 by tguilbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_trim(char *stock)
{
	int		i;
	int		j;
	char	*stk;

	j = 0;
	i = 1;
	while (stock[i - 1] != '\n' && stock[i] != '\0')
		i++;
	while (stock[i + j])
		j++;
	if (!(stk = malloc(sizeof(char) * j + 1)))
		return (NULL);
	j = 0;
	while (stock[i + j])
	{
		stk[j] = stock[i + j];
		j++;
	}
	stk[j] = '\0';
	free(stock);
	stock = NULL;
	return (stk);
}

char	*formate(char *stock)
{
	int		i;
	char	*stk;

	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (!(stk = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
	{
		stk[i] = stock[i];
		i++;
	}
	stk[i] = '\0';
	return (stk);
}

int		joindup(char **stock, char *buffer)
{
	int		i;
	int		j;
	char	*stk;

	if (!(stk = malloc(sizeof(char) * strlen2(*stock, buffer, 0) + 2)))
		return (0);
	i = 0;
	if (*stock)
		while ((*stock)[i])
		{
			stk[i] = (*stock)[i];
			i++;
		}
	j = 0;
	while (buffer[j])
	{
		stk[i + j] = buffer[j];
		j++;
	}
	stk[i + j] = '\0';
	free(*stock);
	*stock = stk;
	return (1);
}

int		ft_read(int fd, char **stock)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	int		i;

	if (-1 == (ret = read(fd, buf, BUFFER_SIZE)))
		return (-1);
	buf[ret] = '\0';
	i = 0;
	if (!(joindup(stock, buf)))
		return (-1);
	if (ret == 0)
		return (0);
	while (buf[i])
		if (buf[i++] == '\n')
			return (1);
	return (ft_read(fd, stock));
}

int		get_next_line(int fd, char **line)
{
	char static	*stock = NULL;
	int			error;
	int			ret;

	if (line == NULL)
		return (-1);
	error = 0;
	ret = 1;
	if (strlen2(stock, 0, 1))
		if (-1 == (ret = ft_read(fd, &stock)))
			error = 1;
	if (error == 0)
		if (NULL == (*line = formate(stock)))
			error = 1;
	if (error == 0)
		if (NULL == (stock = ft_trim(stock)))
			error = 1;
	if (error == 1 || ret == 0)
		free(stock);
	if (error == 1 || ret == 0)
		stock = NULL;
	if (error == 1)
		return (-1);
	return (ret);
}
