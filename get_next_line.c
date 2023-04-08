/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:52 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/08 12:33:17 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gameplan : 1. loops read until a line is completed
		2. add the contents of the buffer to stash
		3. extract the line from stash up to new line
		4. stash is static variable and keeps the content after the new line */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

//if last node of stash contains '\n'
int	contain_nl(t_list *stash)
{
	int			i;
	t_list	*ptr;


	i = 0;
	//only the latest node is relevant so pointer to last node
	ptr = ft_lstlast(stash);
	while (ptr->content[i])
	{
		//if found new line return 1 otherwise return 0
		if (ptr->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

//free stash up to '\n' including '\n'
void	free_stash(t_list **stash)
{
	t_list *tmp;
	t_list *ptr;
	int	i;
	int	j;

	//make new tmp node
	tmp = malloc(sizeof(t_list));
	if (stash == NULL || tmp == NULL)
		return ;
	tmp->next = NULL;
	j = 0;
	i = 0;
	ptr = ft_lstlast(*stash);
	while (ptr->content[i]  && ptr->content[i] != '\n')
		i++;
	if (ptr->content  && ptr->content[i] == '\n')
	i++;
	tmp->content = (char *)malloc(sizeof(char) * ((ft_strlen(ptr->content) - i) + 1));
	if (tmp->content == NULL)
		return ;
	//the content of tmp node is now the content of the last node after new line
	while (ptr->content[i])
		tmp->content[j++] = ptr->content[i++];
	//null terminate tmp
	tmp->content[j] = '\0';
	//free stash and copy tmp to stash
	clear_list(*stash);
	*stash = tmp;
}

//add content from *buf to stash
void	add_to_stash(t_list **stash, char *buf, int read_size)
{
	t_list	*ptr;
	t_list	*new_node;
	int	i;

	//pointer to last node of stash since we want to append buf to it
	ptr = ft_lstlast(*stash);
	//make a new node
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc((sizeof(char) * read_size) + 1);
	if (new_node->content == NULL)
		return ;
	i = 0;
	//the new node content is buf
	while (read_size > 0)
	{
		new_node->content[i] = buf[i];
		i++; 
		read_size--;
	}
	//null terminate new node
	new_node->content[i] = '\0';
	//append new node to stash
	ft_lstadd_back(stash, new_node);
}

//extract_line function extracts line upto '\n' if there is one
char	*extract_line(t_list *stash)
{
	char	*line;
	//int	line_len;
	int	i;
	int	j;
	t_list	*ptr;

	//allocate size enough for stash
	/*
	line_len = BUFFER_SIZE * (ft_lstsize(stash) - 1) + last_node_len(stash);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	*/
	line = (char *)malloc(sizeof(char) * (total_node_len(stash) + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	ptr = stash;
	while (ptr)
	{
		/*
		//if end of line
		if (ptr == NULL)
			break ;
		*/
		//while the content of the node is not end
		while (ptr->content[j])
		{
			//break if new line found
			if (ptr->content[j] == '\n')
			{	
				line[i] = ptr->content[j];
				i++;
				break ;
			}
			//extract content of node to line
			line[i] = ptr->content[j];
			i++;
			j++;
		}
		//reset j to 0 and go to next node
		j = 0;
		ptr = ptr->next;
	}
	//add null terminator to line and return it
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char	*buf;
	char	*line;
	int	read_size;

	//if invalid file or BUFFER_SIZE return NULL
	if (fd < 0 || fd == 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_size = 0;
	//loop until end of file (break when new line character found)
	while (1)
	{
		//allocate memory for buf
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		//read continuously
		read_size = read(fd, buf, BUFFER_SIZE);
		//if end of file
		if (read_size <= 0 && stash != NULL)
		{
			free(buf);
			//extract line from stash
			line = extract_line(stash);
			clear_list(stash);
			//break off loop to return line
			break ;
		}
		//if empty file, return
		else if (read_size <= 0 && stash == NULL)
			return (NULL);
		//null terminate buf
		buf[read_size] = '\0';
		//store buf to stash as linked list
		add_to_stash(&stash, buf, read_size);
		//free buf after storing
		free(buf);
		if (contain_nl(stash) == 1)
		{
			//if new line character is found, extract line from stash up to '\n'
			line = extract_line(stash);
			//free stash until after '\n'
			free_stash(&stash);
			//break to return the line;
			break ;
		}
	}
		if (line[0] == '\0')
		{
			if (stash != NULL)
			{
				clear_list(stash);
				stash = NULL;
			}
			free(line);
			line = NULL;
			return (NULL);
		}
	return (line);
}

//PROBLEM FREE NOT ALLOCATE WHEN SINGLE CHARACTER LIKE "\n"
/*
#include <fcntl.h>
int main()
{
	int fd = open("get_next_line_utils.c", O_RDONLY);
	char *status;

	do
	{
		status = get_next_line(fd);
		if(status != NULL)
			printf("%s", status);
	}while(status != NULL);
	return 0;
}
*/
