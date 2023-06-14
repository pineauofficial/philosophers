/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/14 16:47:24 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*print_hello(void *thread_id)
{
	long			tid;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	tid = (long)thread_id;
	pthread_mutex_lock(&mutex);
	printf("Hello from thread %ld\n", tid);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}

int	threads_join(t_threads **philo, t_struct *data)
{
	int			ptj;
	int			i;
	t_threads	*current;

	current = *philo;
	i = 0;
	while (i < data->philo)
	{
		ptj = pthread_join(current->thread, NULL);
		i++;
		if (ptj != 0)
			return (0);
		current = current->next;
	}
	return (1);
}

void	philosophers(t_struct *data, t_threads **philo)
{
	long		i;
	int			ptc;
	t_threads	*current;

	current = *philo;
	i = 0;
	while (i < data->philo)
	{
		ptc = pthread_create(&current->thread, NULL, print_hello, (void *)i);
		i++;
		current = current->next;
		if (ptc != 0)
			return ;
	}
	if (threads_join(&current, data) == 0)
		return ;
}

void	init(char **argv)
{
	t_struct	*data;
	t_threads	*philo;

	data = malloc(sizeof(t_struct));
	if (!data)
		return ;
	data->philo = ft_atoi(argv[1]);
	data->fork = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	make_list(data, &philo);
	philosophers(data, &philo);
	free(data);
	free_list(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argv);
}
