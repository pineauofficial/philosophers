/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/18 17:03:02 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	make_list(t_struct *data, t_threads **philo)
{
	int			i;

	i = 0;
	*philo = make_nod(i);
	while (++i <= data->philo)
		add_nod(*philo, make_nod(i));
}

void	*make_nod(int num)
{
	t_threads	*new;

	new = malloc(sizeof(t_threads));
	if (!new)
		return (NULL);
	new->num = num;
	new->next = NULL;
	return (new);
}

void	add_nod(t_threads *head, t_threads *new)
{
	t_threads	*current;

	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	free_list(t_threads *head)
{
	t_threads	*current;
	t_threads	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
