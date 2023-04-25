/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:17 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/25 18:17:16 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"
/*
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
*/
t_list	*move_stash_content(t_list *ptr, t_list *tmp, int i)
{
	int			j;

	j = 0;
	while (ptr)
	{
		while (ptr->content[i])
			tmp->content[j++] = ptr->content[i++];
		ptr = ptr->next;
		i = 0;
	}
	tmp->content[j] = '\0';
	return (tmp);
}

void	clear_list(t_list *list)
{
	t_list	*current;
	t_list	*temp;

	current = list;
	while (current)
	{
		free(current->content);
		temp = current->next;
		free(current);
		current = temp;
	}
}

t_list *ft_lstlast(t_list *lst)
{
	t_list *ptr;
	t_list *tmp;
	int	count;

	ptr = lst;
	count = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	tmp  = lst;
	while (count > 1)
	{
		tmp = tmp->next;
		count--;
	}
	return (tmp);
}

int	total_node_len(t_list *lst)
{
	int	i;
	int	len;
	t_list *ptr;

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

t_list	*generate_tmp(t_list *stash, int i)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->content = (char *)malloc(sizeof(char) * ((total_node_len(stash) - i) + 1));
	if (tmp->content == NULL)
		return (NULL);
	return (tmp);
}

void	advance_to_nl(t_list **ptr, int *i)
{
	while (*ptr && (*ptr)->content[*i] != '\n')
	{
		if ((*ptr)->content[*i] == '\0')
		{
			*ptr = (*ptr)->next;
			*i = -1;
		}
		(*i)++;
	}
}

/*
t_list    *generate_tmp_and_advance_to_nl(t_list **ptr, t_list *stash, int *pos)
{
    t_list    *tmp;
    int		i;

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
    if ((*ptr)->content[i] == '\n')
	i++;
    tmp = malloc(sizeof(t_list));
    if (tmp == NULL)
        return (NULL);
    tmp->next = NULL;
    tmp->content = (char *)malloc(sizeof(char) * ((total_node_len(stash) - i) + 1));
    if (tmp->content == NULL)
        return (NULL);
    pos = &i;
    return (tmp);
}
*/
char	*final_line(char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
