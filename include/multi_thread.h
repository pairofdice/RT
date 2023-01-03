/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:28 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/03 12:57:02 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_THREAD_H
# define MULTI_THREAD_H
# include "rt.h"
# include <pthread.h>

# define NUM_THREADS 13
# define NUM_TASKS 35

typedef struct s_multi
{
	pthread_mutex_t	tasks_done_mutex;
	pthread_mutex_t	tasks_taken_mutex;
	pthread_mutex_t	frame_start_mutex;
	pthread_mutex_t	frame_end_mutex;
	pthread_cond_t	frame_start_cv;
	pthread_cond_t	frame_end_cv;
	size_t			tasks_done;
	size_t			tasks_taken;
	pthread_t		threadpool[NUM_THREADS];
	int				frame_n;
	int				threads_done;
}					t_multi;

#endif