/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:58:08 by pineau            #+#    #+#             */
/*   Updated: 2023/05/31 15:54:15 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stddef.h>

typedef struct s_struct
{
	int	philo;
	int	fork;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
}	t_struct;

/*---------MANDATORY---------*/

/*main.c*/
void		philosophers(t_struct *philo);
void		init(char **argv);
int			main(int argc, char **argv);

/*utils.c*/
int			ft_strcmp(char *s1, char *s2);

/*check_args.c*/
int			check_args(int argc, char **argv);
int			ft_atoi(const char *nptr);
int			sizestr(int n);
char		*ft_itoa(int n);
int			check_numbers(char **argv);

#endif