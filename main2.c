/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:00:24 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/21 16:57:23 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"


int draw_mandelbrot(t_stu *stu);

int	mouse_release(int button, int x, int y, struct t_stu *stu)
{
	if (button == 4)
		stu->zoom *= 1.5;
	else if (button == 5)
		stu->zoom /= 1.5;
	draw_mandelbrot (stu);
	return (0);
}

int	arrows(int button, int x, int y, struct t_stu *stu1)
{
	//if (button == 126)
	//{
		//stu->moveX *= 0.1;
		//stu->moveY += 0.1;
	//}
	draw_mandelbrot (stu1);
	return (0);
}

int	key_release(int keycode, int x, int y, struct t_stu *stu)
{
	if (keycode == 53)
		exit (0);
	return (0);
}

int draw_mandelbrot(t_stu *stu)
{
	int k = 0;
	int h = 900;
		int w = 900;

  double pr, pi;           //real and imaginary part of the pixel p
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	  double moveX = stu->moveX, moveY = stu->moveY; //you can change these to zoom and change position
	  double zoom = stu->zoom;
  int color; //the RGB color value for the pixel
  int maxIterations = 256;//after how much iterations the function should stop
  //for(int y = 0; y < 900; y++)
	int y = 0;
	int x = 0;
	int i;
	void *mlx_ptr;
	void *win_ptr;
	mlx_ptr = stu->mlx_ptr;
	win_ptr = stu->win_ptr;
	while (y < 900)
	{
  //for(int x = 0; x < 900; x++)
	x = 0;
	while (x < 900)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
    pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
    newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
    //"i" will represent the number of iterations
    
    //start the iteration process
    //for(i = 0; i < maxIterations; i++)
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
  mlx_pixel_put(mlx_ptr, win_ptr, x, y, 255255255);
	x++;
  }
	y++;
	}
  return (0);
}

int main(int argc, char *argv[])
{
	int k = 0;
	int h = 900;
	int w = 900;
	t_stu *stu;
	void *mlx_ptr; 
	mlx_ptr = mlx_init();
	void *win_ptr; 
	win_ptr = mlx_new_window(mlx_ptr, 900, 900, "test");
  	//each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
	double pr, pi;           //real and imaginary part of the pixel p
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	double zoom = 0.5, moveX = -0.5, moveY = 1; //you can change these to zoom and change position
	stu = (t_stu *)ft_memalloc(sizeof(*stu));
	stu->zoom = 0.5;
	stu->moveX = -0.5;
	stu->moveY = 1;
	stu->mlx_ptr = mlx_ptr;
	stu->win_ptr = win_ptr;
	int color; //the RGB color value for the pixel
	int maxIterations = 256;//after how much iterations the function should stop
	draw_mandelbrot(stu);
	mlx_hook(win_ptr, 2, 0, &arrows, stu);
	mlx_hook(win_ptr, 4, 0, &mouse_release, stu);
	//mlx_hook(stu->win_ptr, 3, 0, &key_release, stu);
	mlx_loop(mlx_ptr);
	return 0;
}
