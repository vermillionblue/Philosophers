/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:50:28 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 23:22:00 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_nums(char **argv)
{
	int	i;
	int	k;

	i = 1;
	while (argv[i])
	{
		k = 0;
		if (ft_atol(argv[i]) > INT_MAX || ft_atol(argv[i]) < INT_MIN)
			return (0);
		while (argv[i][k])
		{
			if (!(ft_isdigit(argv[i][k])))
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

void	check_input(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("4 or 5 arguments needed\n");
		exit (EXIT_FAILURE);
	}
	if (check_nums(argv) == 0)
	{
		printf("Positive integers as arguments are required\n");
		exit (EXIT_FAILURE);
	}
}
