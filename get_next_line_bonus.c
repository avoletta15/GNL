/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:54:11 by marioliv          #+#    #+#             */
/*   Updated: 2023/05/11 15:58:32 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*looping(char *line)
{
	char	*backup;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		if (line[++i] == '\0')
		{
			backup = NULL;
			return (NULL);
		}
		backup = ft_substr(line, i, ft_strlen(line) - (i - 1));
		line[i] = '\0';
		return (backup);
	}
	return (NULL);
}

char	*maria(int fd, char *buffer, char *line)
{
	int	i;

	i = -1; /* read retorna o numero real de bytes lidos, do contrario,
		retorna <0 */
	while (i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
			/* queremos saber em qual posicao da linha o nosso contadro estaa*/
		if (i < 0)
			return (NULL); /* nesse caso, o file nao existe ou deu erro */
		else if (i == 0)   /* nesse caso, o file nao tem nada dentro */
			break ;
		buffer[i] = '\0';
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char *backup[FOPEN_MAX];
		/*static variable --> vai preservar o ultimo valor toda vez que a funcao for chamada. ex.: se o valor inicial = 0
	roda a funcao, o valor passa a ser 10,
		da prxima vez que a funcao for chamada, o valor vai ser 10*/
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || FOPEN_MAX < fd) /* fe = 0 - nao tem file
	/ BUFFER_SIZE <= 0 nao tem "contador de letras para correr a linha"*/
		return (NULL);
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = maria(fd, buffer, backup[fd]);
	free(buffer);
	if (!line)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = looping(line);
	return (line);
}
