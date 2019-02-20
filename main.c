/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:43:05 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/20 16:50:46 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEPTH 100 // iterations depth
//#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
#include <math.h>
#include <mlx.h>
void PutPixel(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
  mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}
void Mandelbrot(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int k = 0;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 900, 900, "test");
  float zi, zr, ci, cr, tmp;
  //-320 -> 320
  for(int i=-900;i<900;i++)
  {
     ci=((float)i)/320.0;
     for(int j=-450;j<225;j++)
     {
        cr=((float)j)/240.0;
        zi=zr=0.0;
        for(k=0;k<DEPTH;k++)
        {
   tmp=zr*zr-zi*zi;
   zi=2*zr*zi+ci;
   zr=tmp+cr;
   if (zr*zr+zi*zi>1.0E16) break;
		}
    if (k<DEPTH)
   PutPixel(mlx_ptr, win_ptr, i+450,j+450,k%3+1+120100100);
    else PutPixel(mlx_ptr, win_ptr, i+450,j+450,180200050);
     }
  }
  mlx_loop(mlx_ptr);
  }
int main(void)
{
  Mandelbrot();
  return 0;
}
