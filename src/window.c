#include "../headers/header.h"

/**
 * init_instance - intialize all instance
 * @in: the given instance
 *
 * Return: 0 on success 1 otherwise
 **/

int init_instance(SDL_Instance *in)
{
	/** if the window is not initialized **/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/** create the windwo with the given width & height **/
	in->win = SDL_CreateWindow("The Maze project", 0, 0, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	/** if window is not created **/
	if (in->win == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/** create the renderer **/
	in->ren = SDL_CreateRenderer(in->win, -1, SDL_RENDERER_ACCELERATED
	| SDL_RENDERER_PRESENTVSYNC);
	/** if renderer is not created **/
	if (in->ren == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/** if the sdl image is not initialized **/
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Failed to initialize SDL_image.\n");
		return (1);
	}
	return (0);
}

/**
 * FixAng - reset the angle if it is above the range
 * @a: the given angle
 *
 * Return: the converted angle
 **/
float FixAng(float a)
{
	/** if the angle is above 360 degeree **/
	if (a > 2 * PI)
		a -= 2 * PI;
	/** if the angle is negative **/
	if (a < 0)
		a += 2 * PI;
	return (a);
}
