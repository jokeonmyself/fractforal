/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:00:24 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/20 18:55:47 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int main(int argc, char *argv[])
{
	void	*mlx_ptr;
	void	*win_ptr;
	int k = 0;
	int h = 900;
		int w = 900;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 900, 900, "test");
 // screen(400, 300, 0, "Mandelbrot Set"); //make larger to see more detail!

  //each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
  double pr, pi;           //real and imaginary part of the pixel p
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
  double zoom = 0.2, moveX = -0.5, moveY = 1; //you can change these to zoom and change position
  int color; //the RGB color value for the pixel
  int maxIterations = 256;//after how much iterations the function should stop

  //loop through every pixel
  for(int y = 0; y < 900; y++)
  {
  for(int x = 0; x < 900; x++)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
    pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
    newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
    //"i" will represent the number of iterations
    int i;
    //start the iteration process
    for(i = 0; i < maxIterations; i++)
    {
      //remember value of previous iteration
      oldRe = newRe;
      oldIm = newIm;
      //the actual iteration, the real and imaginary part are calculated
      newRe = oldRe * oldRe - oldIm * oldIm + pr;
      newIm = 2 * oldRe * oldIm + pi;
      //if the point is outside the circle with radius 2: stop
      if((newRe * newRe + newIm * newIm) > 4) break;
    }
    //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
	color = 000255000 + ((i%256)*1000000) + 255 * (i < maxIterations);
    //color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
     //draw the pixel
  mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
  }
  }
  //make the Mandelbrot Set visible and wait to exit
  //redraw();
  //sleep();
  mlx_loop(mlx_ptr);
  return 0;
}
