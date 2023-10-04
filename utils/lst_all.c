/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:54 by museker           #+#    #+#             */
/*   Updated: 2023/10/04 22:20:23 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *key, void *value)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	p->key = key;
	p->value = (char *)value;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*start;

	if (!lst || !new)
		return ;
	start = *lst;
	new->next = start;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*start;
	t_list	*temp;

	start = *lst;
	while (start)
	{
		temp = start;
		start = start->next;
		free(temp);
	}
	*lst = NULL;
}
