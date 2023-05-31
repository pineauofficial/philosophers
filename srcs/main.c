/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/05/31 17:40:11 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void)
{
	printf(" salut");
	return (0);
}

void	philosophers(t_struct *philo)
{
	pthread_t	i;
	int			j;

	j = philo->philo;
	i = (pthread_t)philo->philo;
	while (j != 0)
	{
		printf("\nthread numero %ld :", i);
		pthread_create(&i, NULL, test(), NULL);
		j--;
		i = (pthread_t)j;
	}
	j = philo->philo;
	while (j != 0)
	{
		pthread_join(i, NULL);
		j--;
		i = (pthread_t)j;
	}
}

void	init(char **argv)
{
	t_struct	*philo;

	philo = malloc(sizeof(t_struct));
	if (!philo)
		return ;
	philo->philo = ft_atoi(argv[1]);
	philo->fork = ft_atoi(argv[1]);
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	philosophers(philo);
	free(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argv);
	write(1, "SALUT\n", 6);
}
