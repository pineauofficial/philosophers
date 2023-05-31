/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:04:52 by pineau            #+#    #+#             */
/*   Updated: 2023/05/31 15:45:55 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5)
		return (0);
	if (check_numbers(argv) == 1)
		return (0);
	//peut etre rajouter une limite pour l taille des nombre
	return (1);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		nbr;
	int		i;
	int		signe;

	i = 0;
	str = (char *)nptr;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	signe = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -signe;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	return (nbr * signe);
}

int	sizestr(int n)
{
	unsigned int	nb;
	int				a;

	nb = n;
	a = 1;
	if (n < 0)
	{
		a++;
		nb = nb * (-1);
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		a++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	unsigned int		size;
	char				*str;
	unsigned int		nb;

	nb = n;
	size = sizestr(nb);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb = nb * (-1);
	}
	str[size] = '\0';
	size = size - 1;
	while (nb >= 10)
	{
		str[size] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	str[size] = nb + '0';
	return (str);
}

int	check_numbers(char **argv)
{
	char	*tmp;
	int		i;

	i = 3;
	while (i > 1)
	{
		tmp = ft_itoa(ft_atoi(argv[i]));
		if (!tmp)
			return (2);
		if (ft_strcmp(tmp, argv[i]) != 0)
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		i--;
	}
	return (0);
}
