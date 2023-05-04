/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:24:31 by marioliv          #+#    #+#             */
/*   Updated: 2023/05/04 19:16:09 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* char	*looping(char *line)
{
	char	*backup;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0') // quando a linha em si ja nao tem nada
		return (NULL);
	backup = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*backup == '\0') // para ter certeza que o byte apos a quebra de linha
	// ou o suposto final da string eh mesmo o final
	{
		free(backup);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (backup);
}
 */

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
			backup = NULL; //causa double free quando o primeiro char lido no line e '\0'
			return (NULL);
		}
		backup = ft_substr(line, i, ft_strlen(line) - (i - 1));
		line[i] = '\0';
		return (backup);
	}
	return (NULL);
	free(backup);
}


char	*get_line(int fd, char *buffer, char *line)
{
	int		i;

	i = -1; // read retorna o numero real de bytes lidos, do contrario, retorna <0
	while (i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (NULL);// nesse caso, o file nao existe
		else if (i == 0) // nesse caso, o file nao tem nada
			break ; 
		/* buffer[i] = '\0'; */
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
	static char	*backup;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0) //BUFFER_SIZE vai ser definido da biblio
		return (NULL);
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL); 
	line = get_line(fd, buffer, backup);
	free(buffer);
	if (!line)
	{
		free(backup);
		return (NULL);
	}
	backup = looping(line); 
	return (line);
}

int main(void)
{
    int     fd;
    char    *line;
    int     check;
	
    check = 1;
    fd = open("teste.txt", O_RDONLY);
    printf("\nBuff_size: %d\n", BUFFER_SIZE);
    while (check)
    {
        line = get_next_line(fd);
        if (!line)
        {
            check = 0;
            printf("\n");
        }
        printf("Line: %s", line);
        free(line);
    }
}