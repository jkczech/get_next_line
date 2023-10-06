/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:41:33 by jkoupy            #+#    #+#             */
/*   Updated: 2023/10/04 14:59:23 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_line(t_list **llist)
{
	t_list	*last;
	char	*leftover;
	int		i;
	int		j;

	if (!*llist)
		return ;
	last = ft_lstlast(*llist);
	i = line_length(last);
	if (!last->content[i])
		return (free_list(llist, NULL));
	j = 0;
	leftover = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!leftover)
		return ;
	while (last->content[i])
		leftover[j++] = last->content[i++];
	leftover[j] = '\0';
	free_list(llist, leftover);
}

//takes the list and returns the full string until newline
char	*read_line(t_list *llist)
{
	char	*line;
	int		i;
	int		j;

	if (!llist || !llist->content)
		return (NULL);
	line = malloc((line_length(llist) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (llist)
	{
		j = 0;
		while (llist->content[j] && llist->content[j] != '\n')
			line[i++] = llist->content[j++];
		if (llist->content[j] == '\n')
		{
			line[i++] = llist->content[j++];
			break ;
		}
		llist = llist->next;
	}
	line[i] = '\0';
	return (line);
}

// returns 1 if finds a newline
// else 0
int	line_ends(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// creates a linked list and reads BUFFER_SIZE bytes each time
// until it finds a buffer smaller than B_S or a \n in it
void	save_line(t_list **llist, int fd)
{
	t_list	*node;
	int		readlen;
	char	*buf;

	if (*llist && line_ends((*llist)->content))
		return ;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return ;
	readlen = read(fd, buf, BUFFER_SIZE);
	if (readlen <= 0)
	{
		free(buf);
		return ;
	}
	buf[readlen] = '\0';
	node = ft_lstnew(buf);
	ft_lstadd_back(llist, node);
	if (!*llist && buf[0])
		*llist = ft_lstnew(buf);
	if (line_ends(buf) || readlen < BUFFER_SIZE)
		return ;
	save_line(llist, fd);
	return ;
}

char	*get_next_line(int fd)
{
	static t_list	*llist;
	char			*next_line;
	t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		while (llist)
		{
			free(llist->content);
			tmp = llist->next;
			free(llist);
			llist = tmp;
		}
		return (NULL);
	}
	save_line(&llist, fd);
	next_line = read_line(llist);
	free_line(&llist);
	return (next_line);
}
