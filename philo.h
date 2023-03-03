/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/03 16:57:39 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int			philo;
	long		t_death;
	long		t_eat;
	long		t_sleep;
	int			nb_eat;
}				t_rules;

typedef struct s_philo
{
	pthread_t	id;
	int			my_fork;
	int			fork;
}				t_philo;

// Utils
long long		get_time(void);
long long		ft_atol(const char *nptr);
void			init_rules(t_rules *rules, int ac, char **av);

#endif
