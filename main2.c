/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <fkhrazz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:00:24 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/27 14:48:52 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include <stdio.h>


int draw_mandelbrot(t_stu *stu);

int	mouse_release(int button, int x, int y, t_stu *stu)
{
	if (button == 4)
		stu->zoom *= 1.5;
	else if (button == 5)
		stu->zoom /= 1.5;
	draw_mandelbrot (stu);
	return (0);
}

int board(int but, t_stu *stu1)
{
	if (stu1->moveX > 1)
			stu1->moveX = 1;
	if (stu1->moveY > 1)
			stu1->moveY = 1;
	if (but == 126)
		stu1->moveY += 0.1;
	if (but == 125)
		stu1->moveY -= 0.1;
	if (but == 123)
		stu1->moveX -= 0.1;
	if (but == 124)
		stu1->moveX += 0.1;
	draw_mandelbrot ((stu1));
	return (0);
}

int	key_release(int keycode, t_stu *stu)
{
	if (keycode == 53)
		exit (0);
	return (0);
}

int draw_mandelbrot(t_stu *stu)
{
	void *mlx_ptr;
	void *win_ptr;
	mlx_ptr = stu->mlx_ptr;
	win_ptr = stu->win_ptr;
	int k = 0;

	//в отдельную функцию создания нового аймеджа
	void *img_ptr;

	img_ptr = mlx_new_image(mlx_ptr, 1800, 1800);

	int *data_addr;

	stu->data_addr = mlx_get_data_addr(img_ptr, &(stu->bits_per_pixel), &(stu->size_line), &(stu->endian));

	data_addr = (int *) stu->data_addr;
	
		int h = 1800;
		int w = 1800;

  	double pr, pi;           //real and imaginary part of the pixel p
  	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	  double moveX = stu->moveX, moveY = stu->moveY; //you can change these to zoom and change position
	  double zoom = stu->zoom;
  	int color; //the RGB color value for the pixel
  	int maxIterations = 256;//after how much iterations the function should stop
		int y = 0;
		int x = 0;
		int i;
		int size_line = stu->size_line;
	
	while (y < h)
	{
		x = 0;
		while (x < w)
  	{
    	//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    	pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
    	pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
    	newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
    	//"i" will represent the number of iterations
			i = 0;
			while (i < maxIterations)
    	{
     	 //remember value of previous iteration
     	 oldRe = newRe;
    	  oldIm = newIm;
    	  //the actual iteration, the real and imaginary part are calculated
     	 newRe = oldRe * oldRe - oldIm * oldIm + pr;
    	  newIm = 2 * oldRe * oldIm + pi;
    	  //if the point is outside the circle with radius 2: stop
    	  if((newRe * newRe + newIm * newIm) > 4)
		 	 break ;
				i++;
    }
		double iops;
		if (i != 0)
		iops = i%256;
		else iops = 0;
		color = 000255000 + (iops*1000000) + 255 * (i < maxIterations);
		data_addr[(stu->size_line / 4) * y + x] = color;
		x++;
  }
	y++;
	}
	mlx_put_image_to_window(stu->mlx_ptr, stu->win_ptr, img_ptr, 0, 0);
  return (0);
}

int main(int argc, char *argv[])
{
	int k = 0;
	int h = 1800;
	int w = 1800;
	t_stu *stu;
	void *mlx_ptr; 
	mlx_ptr = mlx_init();
	void *win_ptr; 
	win_ptr = mlx_new_window(mlx_ptr, 900, 900, "test");
  	//each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
	double pr, pi;           //real and imaginary part of the pixel p
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	double zoom = 0.5, moveX = -0.5, moveY = 1; //you can change these to zoom and change position
	stu = (t_stu *)ft_memalloc(sizeof(t_stu));
	stu->zoom = 0.5;
	stu->moveX = -0.5;
	stu->moveY = 1;
	stu->mlx_ptr = mlx_ptr;
	stu->win_ptr = win_ptr;
	int color; //the RGB color value for the pixel
	int maxIterations = 256;//after how much iterations the function should stop
	draw_mandelbrot(stu);
	mlx_hook(stu->win_ptr, 2, 0, &board, stu);
	mlx_hook(stu->win_ptr, 4, 0, &mouse_release, stu);
	mlx_hook(stu->win_ptr, 3, 0, &key_release, stu);
	mlx_loop(stu->mlx_ptr);
	return 0;
}
