/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:13:59 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/21 16:32:27 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

#include "libft/libft.h"

typedef struct s_stu
{
	double zoom;
	double moveX;
	double moveY;
	struct s_stu *next;
}				t_stu;

#endif
