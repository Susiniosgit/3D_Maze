#include "../headers/header.h"


enemy_t enemy;
/**
 * main - Entry point for execution
 * @argc: the number of argument
 * @argv: vector for the given argument
 *
 * Return: always success
 **/
int main(int argc, char **argv)
{
	/** instance variable **/
	SDL_Instance instance;
	/** create & initialize the window **/
	if (init_instance(&instance) != 0)
		return (1);
	/** initialize the game **/
	init_game();
	if (argc > 1)
		make_map(argv);
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.ren, 76, 76, 76, 0);
		SDL_RenderClear(instance.ren);

		/** handle the input keys from the user **/
		if (poll_events(instance) == 1)
			break;
		/** draw the wall, ceiling, map & sprite **/
		display(instance);
		SDL_RenderPresent(instance.ren);
	}
	/** destroy the renderer & the window & quit**/
	SDL_DestroyRenderer(instance.ren);
	SDL_DestroyWindow(instance.win);
	SDL_Quit();
	return (0);
}

/**
 * display - function to display the game
 * @instance: the given sdl2 instance
 *
 * Return: nothing
 **/
void display(SDL_Instance instance)
{
	ray_cast(instance);
	add_enemy(instance);
	draw_map(instance);
	display_player(instance);
	add_weapon(instance);
	draw_sprite_map(instance);
}

/**
 * init_game - function to initialize the game
 *
 * Return: nothing
 **/
void init_game(void)
{
	/** initialize the player x, y, width, heigth and deltas **/
	player.x = 150;
	player.y = 400;
	player.w = 12;
	player.h = 12;
	player.a = PI3;
	player.dx = cos(player.a) * 5;
	player.dy = sin(player.a) * 5;
}
