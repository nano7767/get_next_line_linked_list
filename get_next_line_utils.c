/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:17 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/28 14:10:04 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

void	clear_list(t_list **list)
{
	t_list	*current;
	t_list	*temp;

	current = *list;
	while (current)
	{
		free(current->content);
		temp = current->next;
		free(current);
		current = temp;
	}
	*list = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;
	t_list	*tmp;
	int		count;

	ptr = lst;
	count = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	tmp = lst;
	while (count > 1)
	{
		tmp = tmp->next;
		count--;
	}
	return (tmp);
}

int	allnodelen(t_list *lst)
{
	int		i;
	int		len;
	t_list	*ptr;

	ptr = lst;
	len = 0;
	while (ptr)
	{	
		i = 0;
		while (ptr->content[i])
		{
			i++;
			len++;
		}
		ptr = ptr->next;
	}
	return (len);
}

t_list	*generate_tmp(int i)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->content = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp->content == NULL)
		return (NULL);
	return (tmp);
}

int	advance_to_nl(t_list **ptr)
{
	int	i;

	if (BUFFER_SIZE == 1)
	{
		while (*ptr && (*ptr)->content[0] != '\n')
			*ptr = (*ptr)->next;
		return (0);
	}
	i = 0;
	while (*ptr && (*ptr)->content[i] != '\n')
	{
		if ((*ptr)->content[i] == '\0')
		{
			*ptr = (*ptr)->next;
			i = -1;
		}
		i++;
	}
	return (i);
}
