/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:02:51 by paradari          #+#    #+#             */
/*   Updated: 2024/12/26 19:02:53 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_rules(t_rules *rules, char **av)
{
	rules->nphilo = ft_atoi(av[1]);
	rules->time2die = ft_atoi(av[2]);
	rules->time2eat = ft_atoi(av[3]);
	rules->time2sleep = ft_atoi(av[4]);
	if (av[5])
		rules->nmeal = ft_atoi(av[5]);
	else
		rules->nmeal = -1;
	rules->s_died = 0;
	rules->s_eat = 0;
	return (0);
}

static t_philos	*ft_init_philo(t_rules *rules)
{
	t_philos	*philo;
	int			i;

	philo = malloc(sizeof(t_philos) * (rules->nphilo));
	if (!philo)
		return (err_null_ret("malloc error!!\n", 0));
	i = 0;
	while (i < rules->nphilo)
	{
		philo[i].philo_nb = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % rules->nphilo;
		philo[i].ate_times = 0;
		philo[i].last_ate_time = 0;
		philo[i].rules = rules;
		i++;
	}
	return (philo);
}

static pthread_mutex_t	*ft_init_forks(t_rules *rules)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * rules->nphilo);
	if (!forks)
		return (err_null_ret("malloc error!!\n", 0));
	i = 0;
	while (i < rules->nphilo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (err_null_ret("mutex error!!\n", 0));
		i++;
	}
	return (forks);
}

int	ft_init_mutex(t_rules *rules)
{
	if (pthread_mutex_init(&(rules->eating_lock), NULL))
		return (err_msg("mutex error!!\n", 1));
	if (pthread_mutex_init(&(rules->writing_lock), NULL))
		return (err_msg("mutex error!!\n", 1));
	rules->forks_lock = ft_init_forks(rules);
	if (!rules->forks_lock)
		return (1);
	rules->philo = ft_init_philo(rules);
	if (!rules->philo)
		return (1);
	return (0);
}
