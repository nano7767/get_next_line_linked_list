/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:52 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/25 18:20:04 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	contain_nl(t_list *stash)
{
	int			i;
	t_list		*ptr;

	ptr = stash;
	while (ptr)
	{
		i = 0;
		while (ptr->content[i])
			if (ptr->content[i++] == '\n')
				return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	free_stash(t_list **stash)
{
	t_list		*tmp;
	t_list		*ptr;
	int			i;
	int			j;

	i = 0;
	ptr = *stash;
	while (ptr && ptr->content[i] != '\n')
	{
		if (ptr->content[i] == '\0')
		{	
			ptr = ptr->next;
			i = -1;
		}
		i++;
	}
	tmp = generate_tmp(*stash, ++i);
	j = 0;
	while (ptr)
	{
		while (ptr->content[i])
			tmp->content[j++] = ptr->content[i++];
		ptr = ptr->next;
		i = 0;
	}
	tmp->content[j] = '\0';
	clear_list(*stash);
	*stash = tmp;
}

void	add_to_stash(t_list **stash, char *buf, int read_size)
{
	t_list	*ptr;
	t_list	*new_node;
	int		i;

	new_node = malloc(sizeof(t_list));
	new_node->content = (char *)malloc((sizeof(char) * read_size) + 1);
	if (new_node->content == NULL || new_node == NULL)
		return ;
	new_node->next = NULL;
	/*
	new_node = malloc(sizeof(t_list));
	new_node = generate_tmp(new_node, -read_size);
	*/
	buf[read_size] = '\0';
	i = 0;
	while (i < read_size)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	ptr = ft_lstlast(*stash);
	ptr->next = new_node;
}

char	*extract_line(t_list *stash)
{
	char		*line;
	int			i;
	int			j;
	t_list		*ptr;

	i = 0;
	line = (char *)malloc(sizeof(char) * (total_node_len(stash) + 1));
	ptr = stash;
	while (ptr)
	{
		j = 0;
		while (ptr->content[j])
		{
			if (ptr->content[j] == '\n')
			{	
				line[i++] = ptr->content[j];
				line[i] = '\0';
				return (line);
			}
			line[i++] = ptr->content[j++];
		}
		ptr = ptr->next;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*buf;
	char			*line;
	int				read_size;

	while (1)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		read_size = read(fd, buf, BUFFER_SIZE);
		if ((!stash && !read_size) || read_size == -1 || BUFFER_SIZE <= 0)
			return (free(buf), NULL);
		if (read_size == 0 && stash && contain_nl(stash) == 0)
		{
			free(buf);
			line = extract_line(stash);
			clear_list(stash);
			stash = NULL;
			break ;
		}
		add_to_stash(&stash, buf, read_size);
		free(buf);
		if (contain_nl(stash) != 0)
		{
			line = extract_line(stash);
			free_stash(&stash);
			break ;
		}
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

/*
char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*buf;
	char			*line = NULL;
	int				read_size;

	while (BUFFER_SIZE <= 0 && buf && read_size != -1)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == 0 && stash != NULL && contain_nl(stash) == 0)
		{
			free(buf);
			line = extract_line(stash);
			clear_list(stash);
			stash = NULL;
			break ;
		}
		buf[read_size] = '\0';
		add_to_stash(&stash, buf, read_size);
		free(buf);
		if (contain_nl(stash) != 0)
		{
			line = extract_line(stash);
			free_stash(&stash);
			break ;
		}
	}
	if (line && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
*/
/*
#include <fcntl.h>
int main()
{
	int fd = open("test2.txt", O_RDONLY);
	char *status;
	int	i;

	i = 0;
	status = "a";
	while(status != NULL)
	{
		status = get_next_line(fd);
		printf("%i %s", i, status);
		i++;
	}
}
*/
/*
	do
	{
		status = get_next_line(fd);
		if(status != NULL)
			printf("%s", status);
	}while(status != NULL);
	return 0;
}
*/
