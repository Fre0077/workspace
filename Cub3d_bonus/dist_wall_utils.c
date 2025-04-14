/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:34 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/14 17:23:59 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit(t_data *data, t_viktor tmp)
{
	char	c;

	if (tmp.x < 0 || tmp.y < 0)
		return (0);
	c = data->map[(int)tmp.y][(int)tmp.x];
	if (c == '1' || c == 'P')
		return (1);
	else
		return (0);
}

double	r(double angle)
{
	int	tmp;

	tmp = angle;
	angle -= tmp;
	tmp = tmp % 90;
	return (angle + tmp);
}

double	rad(double rad)
{
	static double	radd;

	if (rad != -1)
		radd = rad;
	return (radd);
}

double	mult_of_90(double num, char direct)
{
	double	rest;

	rest = r(num);
	if (rest == 0 && direct == '<')
		num = (int)(((int)(num / 90) - 1) * 90);
	else if (direct == '<')
		num = (int)(((int)(num / 90)) * 90);
	else
		num = (int)(((int)(num / 90) + 1) * 90);
	return (num);
}

double	calc_angle(double angle, double cost, char sign)
{
	double	supp;

	if (sign == '-')
	{
		angle = angle - cost;
		supp = mult_of_90(angle, '<');
		if ((int)(supp / 90) % 2 == 1)
			supp = mult_of_90(angle, '>');
		return (fabs(supp - angle));
	}
	else
	{
		angle = angle + cost;
		supp = mult_of_90(angle, '>');
		if ((int)(supp / 90) % 2 == 1)
			supp = mult_of_90(angle, '<');
		return (fabs(supp - angle));
	}
}
