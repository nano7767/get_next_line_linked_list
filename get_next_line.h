/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:40:08 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/28 14:42:07 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 43
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int		contain_nl(t_list *stash);
void	free_stash(t_list **stash);
void	add_to_stash(t_list **stash, char *buf, int read_size);
char	*extract_line(t_list *stash);
void	clear_list(t_list **list);
int		allnodelen(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*generate_tmp(int i);
int		advance_to_nl(t_list **ptr);

#endif
