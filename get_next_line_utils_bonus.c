/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoupy <jkoupy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:41:36 by jkoupy            #+#    #+#             */
/*   Updated: 2023/10/06 17:26:48 by jkoupy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_list(t_list **llist, char *new_content)
{
	t_list	*tmp;

	while (*llist)
	{
		free((*llist)->content);
		tmp = (*llist)->next;
		free(*llist);
		*llist = tmp;
	}
	if (new_content)
		*llist = ft_lstnew(new_content);
}

int	line_length(t_list *llist)
{
	int	i;
	int	len;

	len = 0;
	if (!llist || !llist->content[0])
		return (0);
	while (llist)
	{
		i = 0;
		while (llist->content[i])
		{
			if (llist->content[i] == '\n')
				return (len + i + 1);
			i++;
		}
		len += i;
		llist = llist->next;
	}
	return (len);
}

void	ft_lstadd_new(t_list **lst, char *new_content)
{
	t_list	*temp;
	t_list	*new;

	new = ft_lstnew(new_content);
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
#include <stdio.h>

void	print_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		printf("(null)");
		return ;
	}
	printf("\"");
	while (str[i])
	{
		if (str[i] == '\n')
			printf("\\n");
		else
			printf("%c", str[i]);
		i++;
	}
	printf("\"");
}

void	print_list(t_list *ll)
{
	int cnt;

	cnt = 0;
	if (!ll)
		printf("\tempty list\n");
	while (ll)
	{
		printf("\tNode %d: ", cnt++);
		print_nl(ll->content);
		printf("\n");
		ll = ll->next;
	}
}
*/
