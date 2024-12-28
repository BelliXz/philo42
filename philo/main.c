/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:03:00 by paradari          #+#    #+#             */
/*   Updated: 2024/12/27 10:22:46 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_is_valid_av(int ac, char **av)
{
	int	i;
	int	x;

	i = 1;
	while (i < ac)
	{
		if (!ft_is_digit(av[i]))
			return (1);
		x = ft_atoi(av[i]);
		if (i == 1 && (x < 1 || x == -1))
			return (1);
		if (x < 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
		return (err_msg("wrong format of arguments!!", 1));
	if (ft_is_valid_av(ac, av))
		return (err_msg("input error!!\n", 1));
	if (ft_init_rules(&rules, av))
		return (1);
	if (ft_init_mutex(&rules))
		return (1);
	if (ft_start_sim(&rules))
		return (err_msg("creating thread error!!\n", 1));
}

// printf ("\n----check----\n");
// 	int i=0;
// 	t_philos *philo;
// 	philo = rules.philo;
// 	while (i < rules.nphilo)
// 	{
// 		printf("id %d : lf=%d rf=%d ate=%d lastate=%lld\n", philo[i].philo_nb, philo[i].left_fork, philo[i].right_fork, philo[i].ate_times, philo[i].last_ate_time);
// 		printf("rules : %d %d %d\n", philo[i].rules->time2die, philo[i].rules->time2eat, philo[i].rules->time2sleep);
// 		i++;
// 	}