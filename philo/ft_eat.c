/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:26:35 by kdanchal          #+#    #+#             */
/*   Updated: 2024/09/22 16:26:45 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_control);
	if ((philo->number_of_eat_now == philo->data->number_of_must_eat)
		&& (philo->one_full == 0))
	{
		philo->one_full = 1;
		philo->data->human_qty_full++;
		pthread_mutex_unlock(&philo->data->mutex_control);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_right]);
		return ("full");
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
	return (NULL);
}

void	ft_left_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_left]);
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
	{
		printf("%lu	%d has taken a fork\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_right]);
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
	{
		printf("%lu	%d has taken a fork\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
}

void	ft_right_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_right]);
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
	{
		printf("%lu	%d has taken a fork\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->fork_left]);
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
	{
		printf("%lu	%d has taken a fork\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
}

void	ft_begin_eat_full_or_finish_eat_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_control);
	philo->time_last_meal = ft_time_now_ms();
	philo->number_of_eat_now++;
	pthread_mutex_unlock(&philo->data->mutex_control);
}

void	ft_eat(t_philo *philo)
{
	if (philo->order % 2 == 0
		|| philo->order == philo->data->number_of_philosophers)
		ft_right_left(philo);
	else
		ft_left_right(philo);
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
		printf("%lu	%d is eating\n", ft_time_now_ms() - philo->data->time_start,
			philo->order);
	pthread_mutex_unlock(&philo->data->mutex_control);
	ft_usleep(philo->data->time_to_eat);
	ft_begin_eat_full_or_finish_eat_full(philo);
	if (ft_philo_full(philo))
		return ;
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->fork_left]);
}
