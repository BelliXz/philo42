/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:03:26 by paradari          #+#    #+#             */
/*   Updated: 2024/12/28 13:39:52 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat_left2right(t_philos *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->forks_lock[philo->left_fork]);
	ft_writing(philo->philo_nb, "has taken a fork", rules);
	pthread_mutex_lock(&rules->forks_lock[philo->right_fork]);
	ft_writing(philo->philo_nb, "has taken a fork", rules);
	pthread_mutex_lock(&rules->eating_lock);
	ft_writing(philo->philo_nb, "is eating", rules);
	philo->last_ate_time = get_time_in_ms();
	pthread_mutex_unlock(&(rules->eating_lock));
	ft_sleeping(rules->time2eat, rules);
	(philo->ate_times)++;
	pthread_mutex_unlock(&rules->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&rules->forks_lock[philo->right_fork]);
}

static void	eat_right2left(t_philos *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->forks_lock[philo->right_fork]);
	ft_writing(philo->philo_nb, "has taken a fork", rules);
	pthread_mutex_lock(&rules->forks_lock[philo->left_fork]);
	ft_writing(philo->philo_nb, "has taken a fork", rules);
	pthread_mutex_lock(&rules->eating_lock);
	ft_writing(philo->philo_nb, "is eating", rules);
	philo->last_ate_time = get_time_in_ms();
	pthread_mutex_unlock(&(rules->eating_lock));
	ft_sleeping(rules->time2eat, rules);
	(philo->ate_times)++;
	pthread_mutex_unlock(&rules->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&rules->forks_lock[philo->left_fork]);
}

static void	*lonely_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->rules->forks_lock[philo->left_fork]);
	ft_writing(philo->philo_nb, "has taken a fork", philo->rules);
	ft_sleeping(philo->rules->time2die, philo->rules);
	pthread_mutex_unlock(&philo->rules->forks_lock[philo->left_fork]);
	return (NULL);
}

static void	*routine(void *data)
{
	// (void)data;
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->rules->nmeal == 0)
		return (NULL);
	if (philo->rules->nphilo == 1)
		return (lonely_philo(philo));
	// pthread_mutex_lock(&philo->rules->eating_lock);
	while (!(philo->rules->s_died))
	{
		// pthread_mutex_unlock(&philo->rules->eating_lock);
		if (philo->philo_nb % 2)
			eat_left2right(philo);
		else
			eat_right2left(philo);
		// pthread_mutex_lock(&philo->rules->eating_lock);
		if (philo->rules->s_eat)
		{
		// pthread_mutex_unlock(&philo->rules->eating_lock);
			break ;
		}
		ft_writing(philo->philo_nb, "is sleeping", philo->rules);
		ft_sleeping(philo->rules->time2sleep, philo->rules);
		ft_writing(philo->philo_nb, "is thinking", philo->rules);
		if (philo->rules->nphilo % 2 != 0)
			ft_sleeping((philo->rules->time2eat * 2) - philo->rules->time2sleep,
				philo->rules);
	}
	return (NULL);
}


int	ft_start_sim(t_rules *rules)
{
	t_philos	*philo;
	int			i;

	philo = rules->philo;
	i = 0;
	rules->start_time = get_time_in_ms();
	while (i < rules->nphilo)
	{
		philo[i].last_ate_time = get_time_in_ms();
		if (pthread_create(&(philo[i].id), NULL, routine, &philo[i]))
			return (1);
		i++;
	}
	ft_is_dead_or_all_ate(rules, philo);
	ft_end_sim(rules, philo);
	return (0);
}

// int	ft_start_sim(t_rules *rules)
// {
// 	t_philos	*philo;
// 	int			i;

// 	philo = rules->philo;
// 	i = 0;
// 	rules->start_time = get_time_in_ms();
// 	while (i < rules->nphilo)
// 	{
// 		if (pthread_create(&(philo[i].id), NULL, routine, &philo[i]))
// 			return (1);
// 		philo[i].last_ate_time = get_time_in_ms();
// 		i++;
// 	}
// 	ft_is_dead_or_all_ate(rules, philo);
// 	ft_end_sim(rules, philo);
// 	return (0);
// }