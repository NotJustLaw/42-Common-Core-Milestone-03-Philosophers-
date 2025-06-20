/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justlaw <justlaw@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:11:29 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/19 19:24:35 by justlaw          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct	s_config
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				simulation_end;
	pthread_mutex_t	log;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_end_mutex;
}		t_config;

typedef struct	s_philo
{
	long		idx;
	long		lm_stamp;
	t_config	*infoptr;
	pthread_t	id;
	
}		t_philo;



#endif