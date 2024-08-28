/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:20:10 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/02/13 11:26:18 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

#define COLOR_CYAN    "\x1b[1;36m"
#define COLOR_RESET   "\x1b[0m"

static char	*free_stuff(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

static char	*search_backup(char *line, char **next_line)
{
	size_t	i;
	char	*new_backup;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		*next_line = ft_substr(line, 0, i + 1);
	else
		*next_line = ft_substr(line, 0, i);
	if (!(*next_line))
		return (0);
	if (line[i] == '\n')
	{
		new_backup = ft_substr(line, i + 1, ft_strlen(line) - i);
		if (!new_backup || *new_backup == '\0')
			return (free_stuff(&new_backup));
		return (new_backup);
	}
	if (!(*next_line) || *next_line[0] == '\0')
		free_stuff(&(*next_line));
	return (0);
}

static char	*search_line(int fd, char *buffer, char **backup)
{
	int		len_buf;
	char	*temp_backup;

	len_buf = 1;
	while (1)
	{
		len_buf = read(fd, buffer, BUFFER_SIZE);
		if (len_buf < 0)
			return (0);
		if (len_buf == 0)
			break ;
		buffer[len_buf] = '\0';
		if (!*backup)
			*backup = ft_strdup("");
		if (!*backup)
			return (0);
		temp_backup = *backup;
		*backup = ft_strjoin(temp_backup, buffer);
		free_stuff(&temp_backup);
		if (!*backup)
			return (0);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*backup);
}

char	*get_next_line(int fd)
{
	char		*read_buffer;
	static char	*backup;
	char		*whole_line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (backup && (ft_strchr(backup, '\n')))
	{
		whole_line = ft_strdup(backup);
		free_stuff(&backup);
	}
	else
	{
		read_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!read_buffer)
			return (free_stuff(&backup));
		whole_line = search_line(fd, read_buffer, &backup);
		free(read_buffer);
	}
	if (!whole_line)
		return (free_stuff(&backup));
	backup = search_backup(whole_line, &next_line);
	free_stuff(&whole_line);
	return (next_line);
}

// void	print_next_line(int fd)
// {
// 	char	*next_line;
// 	int		i;

// 	i = 0;
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("%d: %s", i, next_line);
// 		if (next_line == 0)
// 		{
// 			if (next_line == (char *)-1)
// 			{
// 				printf("read error");
// 			}
// 			break ;
// 		}
// 		free(next_line);
// 		i++;
// 	}
// 	printf("\n			\n");
// 	return ;
// }

// int	main(void) {
// 	int		fd1 = 0;
// 	int		fd2 = 0;
// 	int		fd3 = 0;
// 	int		fd4 = 0;
// 	int		fd5 = 0;

// 	fd1 = open("giant_line.txt", O_RDONLY);
// 	if (fd1 == -1) {
// 		printf("fd1: Fout bij openen van bestand");
// 		return (1);
// 	}
// 	printf("fd1:\n");
// 	print_next_line(fd1);

// 	fd2 = open("1char.txt", O_RDONLY);
// 	if (fd2 == -1) {
// 		printf("fd2: Fout bij openen van bestand");
// 		return (1);
// 	}
// 	printf("fd2:\n");
// 	print_next_line(fd2);

// 	fd3 = open("variable_nls.txt", O_RDONLY);
// 	if (fd3 == -1) {
// 		printf("fd3: Fout bij openen van bestand");
// 		return (1);
// 	}
// 	printf("fd3:\n");
// 	print_next_line(fd3);

// 	fd4 = open("giant_line_nl.txt", O_RDONLY);
// 	if (fd4 == -1) {
// 		printf("fd4: Fout bij openen van bestand");
// 		return (1);
// 	}
// 	printf("fd4:\n");
// 	print_next_line(fd4);

// 	fd5 = open("multiple_nl.txt", O_RDONLY);
// 	if (fd5 == -1) {
// 		printf("fd5: Fout bij openen van bestand");
// 		return (1);
// 	}
// 	printf("fd5:\n");
// 	print_next_line(fd5);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	close(fd5);
// 	return 0;
// }