/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:17 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/10 15:27:31 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (srclen);
	while ((src[i] != '\0') && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s3;

	i = 0;
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		while (s1[i] != '\0')
		{
			s3[i] = s1[i];
			i++;
		}
		while (s2[i - ft_strlen(s1)] != '\0')
		{	
			s3[i] = s2[i - ft_strlen(s1)];
			i++;
		}
	}
	s3[i] = '\0';
	return (s3);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	i = 0;
	ptr = malloc(count * size);
	if (ptr != NULL)
	{	
		ft_bzero(ptr, count * size);
	}
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) *(ft_strlen(s1) + 1));
	if (dest != NULL)
	{
		while (s1[i] != '\0')
		{
			dest[i] = s1[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
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

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*ptr;

	len = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	return (len);
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

int	last_node_len(t_list *lst)
{
	int		len;
	t_list	*ptr;

	len = 0;
	ptr = ft_lstlast(lst);
	while (ptr->content[len])
	{
		if (ptr->content[len] == '\n')
		{
			len++;
			break;
		}
		len++;
	}
	len++;
	return (len);
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *ptr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	current;
	char	*sub;
	size_t	new_len;

	if (s == NULL)
		return (NULL);
	else if (ft_strlen(s) <= start || len == 0)
		return (ft_strdup(""));
	i = 0;
	current = start;
	new_len = len;
	if (len > ft_strlen(&s[start]))
		new_len = ft_strlen(&s[start]);
	sub = (char *)malloc((new_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < new_len && current < new_len + current)
	{
		current = start + i;
		sub[i] = s[current];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
