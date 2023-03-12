/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/12 16:21:01 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		ft_eat(philo);
		if (my_meal(philo))
			break ;
		ft_logs(philo, "is sleeping");
		ft_usleep(philo->rules->t_sleep);
		ft_logs(philo, "is thinking");
		pthread_mutex_lock(&philo->rules->death);
		if (philo->rules->death_flag == 1)
		{
			pthread_mutex_unlock(&philo->rules->death);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->death);
	}
	return (NULL);
}

int	check_meal(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].eat_info);
		if (rules->philo[i].nb_eat < rules->nb_eat)
		{
			pthread_mutex_unlock(&rules->philo[i].eat_info);
			return (0);
		}
		pthread_mutex_unlock(&rules->philo[i].eat_info);
	}
	return (1);
}

int	check_death(t_rules *rules, int i)
{
	long long	time;

	pthread_mutex_lock(&rules->philo[i].eat_info);
	time = get_time() - rules->philo[i].last_eat;
	if (time >= rules->t_death)
	{
		pthread_mutex_unlock(&rules->philo[i].eat_info);
		pthread_mutex_lock(&rules->death);
		rules->death_flag = 1;
		pthread_mutex_unlock(&rules->death);
		ft_logs(&rules->philo[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&rules->philo[i].eat_info);
	return (0);
}

void	*ft_death(void *args)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)args;
	while (1)
	{
		if (rules->nb_eat != -1 && check_meal(rules))
			break ;
		i = -1;
		while (++i < rules->n_philo)
			if (check_death(rules, i))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	ft_thread(t_rules *rules)
{
	pthread_t	id_err;
	int			i;

	i = -1;
	while (++i < rules->n_philo)
		pthread_create(&rules->philo[i].t_id, NULL, ft_philo,
			&rules->philo[i]);
	pthread_create(&id_err, NULL, ft_death, rules);
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philo[i].t_id, NULL);
	pthread_join(id_err, NULL);
	ft_free(rules);
}
