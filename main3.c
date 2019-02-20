/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhrazz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:00:24 by fkhrazz           #+#    #+#             */
/*   Updated: 2019/02/20 18:57:12 by fkhrazz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int argc, char *argv[])
{
  screen(320, 240, 0, "Mandelbrot Explorer");

  //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  double pr, pi;           //real and imaginary part of the pixel p
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
  double zoom = 1, moveX = 2, moveY = 2; //you can change these to zoom and change position
  ColorRGB color; //the RGB color value for the pixel
  int maxIterations = 128; //after how much iterations the function should stop

  double time, oldTime, frameTime; //current and old time, and their difference (for input)
  int showText = 0;

  //begin main program loop
  while(!done())
  {
    //draw the fractal
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
      //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
      pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
      pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
      newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
      //i will represent the number of iterations
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
      color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
      //draw the pixel
      pset(x, y, color);
    }

    //print the values of all variables on screen if that option is enabled
    if(showText <= 1)
    {
      print("X:", 1, 1, RGB_White, 1); print(moveX, 17, 1, RGB_White, 1);
      print("Y:", 1, 9, RGB_White, 1); print(moveY, 17, 9, RGB_White, 1);
      print("Z:", 1, 17, RGB_White, 1); print(zoom, 17, 17, RGB_White, 1);
      print("N:", 1, 25, RGB_White, 1); print(maxIterations, 17, 25, RGB_White, 1);
    }
    //print the help text on screen if that option is enabled
    if(showText == 0)
    {
      print("Arrows move (X,Y), Keypad +,- zooms (Z)", 1, h - 25, RGB_White, 1);
      print("Keypad *,/ changes iterations (N)    ", 1, h - 17, RGB_White, 1);
      print("a to z=presets (qwerty), F1=cycle texts", 1, h - 9, RGB_White, 1);
    }
    redraw();

    //get the time and old time for time dependent input
    oldTime = time;
    time = getTicks();
    frameTime = time - oldTime;
    readKeys();
    //ZOOM keys
    if(keyDown(SDLK_KP_PLUS))  {zoom *= pow(1.001, frameTime);}
    if(keyDown(SDLK_KP_MINUS)) {zoom /= pow(1.001, frameTime);}
    //MOVE keys
    if(keyDown(SDLK_DOWN))  {moveY += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_UP))  {moveY -= 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_RIGHT)) {moveX += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_LEFT))  {moveX -= 0.0003 * frameTime / zoom;}
    //keys to change number of iterations
    if(keyPressed(SDLK_KP_MULTIPLY)) {maxIterations *= 2;}
    if(keyPressed(SDLK_KP_DIVIDE))   {if(maxIterations > 2) maxIterations /= 2;}
    //key to change the text options
    if(keyPressed(SDLK_F1)) {showText++; showText %= 3;}
  }
  return 0;
}
