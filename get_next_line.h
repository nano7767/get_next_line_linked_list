/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:40:08 by svikornv          #+#    #+#             */
/*   Updated: 2023/04/25 18:16:06 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	clear_list(t_list *list);
int	ft_lstsize(t_list *lst);
int	total_node_len(t_list *lst);
int	last_node_len(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*move_stash_content(t_list *ptr, t_list *tmp, int i);
//t_list	*generate_tmp_and_advance_to_nl(t_list **ptr, t_list *stash, int *pos);

t_list	*generate_tmp(t_list *stash, int i);
void	advance_to_nl(t_list **ptr, int *i);
char	*final_line(char *line);

#endif
