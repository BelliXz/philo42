/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:02:37 by paradari          #+#    #+#             */
/*   Updated: 2024/12/28 13:41:53 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	ft_sleeping(long long sleeptime, t_rules *rules)
{
	long long	s_time;
	long long	e_time;

	s_time = get_time_in_ms();
	while (!rules->s_died)
	{
		e_time = get_time_in_ms();
		if ((e_time - s_time) >= sleeptime)
			break ;
		usleep (50);
	}
}

void	ft_writing(int id, char *str, t_rules *rules)
{
	pthread_mutex_lock(&rules->writing_lock);
	if (!rules->s_died)
	{
		printf("%lli %i %s\n", get_time_in_ms() - rules->start_time, id + 1, str);
	}
	pthread_mutex_unlock(&rules->writing_lock);
	return ;
}


void	ft_is_dead_or_all_ate(t_rules *r, t_philos *p)
{
	int i;

	while (!(r->s_eat))
	{
		i = -1;
		while (++i < r->nphilo && !(r->s_died))
		{
			pthread_mutex_lock(&(r->eating_lock));
			if ((get_time_in_ms() - p[i].last_ate_time) > r->time2die)
			{
				ft_writing(i, "died", r);
				r->s_died = 1;
			}
			pthread_mutex_unlock(&(r->eating_lock));
			usleep(100);
		}
		if (r->s_died == 1)
			break ;
		i = 0;
		while (r->nmeal != -1 && i < r->nphilo && p[i].ate_times >= r->nmeal)
			i++;
		if (i == r->nphilo)
			r->s_eat = 1;
	}
}

void	ft_end_sim(t_rules *rules, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < rules->nphilo)
	{
		pthread_join(philo[i].id, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&rules->eating_lock);
	pthread_mutex_destroy(&rules->writing_lock);
	while (i < rules->nphilo)
	{
		pthread_mutex_destroy(&rules->forks_lock[i]);
		i++;
	}
	ft_free_in_rules(rules);
}