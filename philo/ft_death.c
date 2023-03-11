/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:52:31 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/10 17:26:00 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].n_eat);
		if (rules->philo[i].nb_eat < rules->nb_eat)
		{
			pthread_mutex_unlock(&rules->philo[i].n_eat);	
			return (0);
		}
		pthread_mutex_unlock(&rules->philo[i].n_eat);
	}
	return (1);
}

void	*ft_death(void *args)
{
	t_rules *rules;
	int	i;
	int	j;

	rules = (t_rules *)args;
	while (1)
	{
		if (rules->nb_eat != -1 && check_meal(rules))
			break;
		i = -1;
		while (++i < rules->n_philo)
		{
			pthread_mutex_lock(&rules->philo[i].l_eat);
			if (get_time() - rules->philo[i].last_eat > rules->t_death)
			{
				pthread_mutex_unlock(&rules->philo[i].l_eat);
				j = -1;
				while (++j < rules->n_philo)
					pthread_detach(rules->philo[j].t_id);
				logs(&rules->philo[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&rules->philo[i].l_eat);
		}
		ft_usleep(1);
	}
	return (NULL);
}
