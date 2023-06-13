/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/13 16:19:41 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_threads	make_list(t_struct *data)
{
	int			i;
	t_threads	*philo;

	i = 0;
	philo = make_nod(i);
	if (!philo)
		return (NULL);
	while (++i <= data->philo)
		add_nod(philo, make_nod(i));
	return (philo);
}

void	*make_nod(int num)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->num = num;
	new->next = NULL;
	return (new);
}

void	add_nod(t_list *head, t_list *new)
{
	t_list	*current;

	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
