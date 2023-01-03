/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread_worker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:58:50 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/03 13:07:39 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	worker_wait(t_main *ctx)
{
	ctx->multi.threads_done++;
	pthread_mutex_unlock(&ctx->multi.tasks_taken_mutex);
	pthread_mutex_lock(&ctx->multi.frame_start_mutex);
	pthread_cond_wait(&ctx->multi.frame_start_cv,
		&ctx->multi.frame_start_mutex);
	pthread_mutex_unlock(&ctx->multi.frame_start_mutex);
}

void	worker_task(int *task_n, t_main *ctx)
{
	*task_n = ctx->multi.tasks_taken;
	ctx->multi.tasks_taken++;
	pthread_mutex_unlock(&ctx->multi.tasks_taken_mutex);
	render_image(ctx, *task_n, ctx->settings.ant_al);
	pthread_mutex_lock(&ctx->multi.tasks_done_mutex);
	ctx->multi.tasks_done++;
}

void	worker_broadcast(t_main *ctx)
{
	ctx->multi.tasks_taken++;
	pthread_mutex_unlock(&ctx->multi.tasks_done_mutex);
	pthread_mutex_lock(&ctx->multi.frame_end_mutex);
	while (ctx->multi.threads_done < (NUM_THREADS - 1))
		ft_putstr("");
	pthread_cond_broadcast(&ctx->multi.frame_end_cv);
	pthread_mutex_unlock(&ctx->multi.frame_end_mutex);
}
