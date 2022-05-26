#include "../headers/header.h"

player_t player;
btn_keys btnkeys;

/**
 * poll_events - function to handle events
 * @ins: the istance of SDL
 *
 * Return: 0 on suceesss 1 otherwise
 **/
int poll_events(SDL_Instance ins)
{
	SDL_Event ev;

	/** while quit & esape key not pressed **/
	while (SDL_PollEvent(&ev))
	{
		/** if quit button is pressed **/
		if (ev.type == SDL_QUIT)
			return (1);
		/** if down key button is pressed **/
		else if (ev.type == SDL_KEYDOWN)
		{
			key_down(ev);
			if (btnkeys.x == 1)
				return (1);
		}
		/** if up key button is pressed **/
		else if (ev.type == SDL_KEYUP)
			key_up(ev);
		/** handle the down key buttons **/
		handle_key_down(ins);
	}
	return (0);
}

/**
 * handle_key_down - handle when the key pressed down
 * @ins: the given instance
 *
 * Return: nothing
 **/
void handle_key_down(SDL_Instance ins)
{
	int mx, my, px = player.x / map_s, py = player.y / map_s, xo = 0, yo = 0;

	xo = (player.dx < 0) ? -20 : 20, yo = (player.dy < 0) ? -20 : 20;
	/** if a key pressed **/
	if (btnkeys.a == 1)
	{
		player.a -= 0.1, player.a = FixAng(player.a);
		player.dx = cos(player.a) * 5, player.dy = sin(player.a) * 5;
	}
	/** if d key pressed **/
	else if (btnkeys.d == 1)
	{
		player.a += 0.1, player.a = FixAng(player.a);
		player.dx = cos(player.a) * 5, player.dy = sin(player.a) * 5;
	}
	else if (btnkeys.w == 1) /** if w key pressed **/
	{
		mx = ((player.dx * 5) + player.x + xo) / map_s;
		my = ((player.dy * 5) + player.y + yo) / map_s;
		if (getmap_value(mx, py, 0) == 0)
			player.x += player.dx * 2;
		if (getmap_value(px, my, 0) == 0)
			player.y += player.dy * 2;
	}
	else if (btnkeys.s == 1) /** if s key pressed **/
	{
		mx = ((player.x - (player.dx * 5)) - xo) / map_s;
		my = ((player.y - (player.dy * 5)) - yo) / map_s;
		if (getmap_value(mx, py, 0) == 0)
			player.x -= player.dx * 2;
		if (getmap_value(px, my, 0) == 0)
			player.y -= player.dy * 2;
	}
	else if (btnkeys.e == 1) /** if e key presse **/
		handle_door();
	/** set the drawing color & draw the required items **/
	SDL_SetRenderDrawColor(ins.ren, 76, 76, 76, 0);
	SDL_RenderClear(ins.ren);
	display(ins);
	SDL_RenderPresent(ins.ren);
}
/**
 * handle_door - function to handle the door open activity
 *
 * Return: nothing
 **/
void handle_door(void)
{
	int px_add_off, py_add_off, mx, my, xo, yo;

	xo = (player.dx < 0) ? -30 : 30;
	yo = (player.dy < 0) ? -50 : 50;
	px_add_off = (player.x + xo) / map_s;
	py_add_off = (player.y + yo) / map_s;
	mx = px_add_off, my = py_add_off;
	/**
	 *printf("mx=%d, my=%d dx=%f dy=%f\n", mx, my, player.dx, player.dy);
	**/
	/** if the player is neear to the door **/
	if (getmap_value(mx, my, 0) == 4)
		setmap_value(mx, my, 0);
}
/**
 * key_down - function to handle key down event
 * @ev: the given event
 *
 * Return: nothing
 **/
void key_down(SDL_Event ev)
{
	/** if left or a key pressed **/
	if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
		btnkeys.a = 1;
	/** if right or d key pressed **/
	if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
		btnkeys.d = 1;
	/** if up or w key pressed **/
	if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
		btnkeys.w = 1;
	/** if down or s key pressed **/
	if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
		btnkeys.s = 1;
	/** if e key pressed **/
	if (ev.key.keysym.sym == SDLK_e)
		btnkeys.e = 1;
	/** if escape button pressed **/
	if (ev.key.keysym.sym == SDLK_ESCAPE)
		btnkeys.x = 1;
}

/**
 * key_up - function to handle key up event
 * @ev: the given event
 *
 * Return: nothing
 **/
void key_up(SDL_Event ev)
{
	/** if left or a key pressed **/
	if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
		btnkeys.a = 0;
	/** if right or d key pressed **/
	if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
		btnkeys.d = 0;
	/** if up or w key pressed **/
	if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
		btnkeys.w = 0;
	/** if down or s key pressed **/
	if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
		btnkeys.s = 0;
	/** is e key pressed **/
	if (ev.key.keysym.sym == SDLK_e)
		btnkeys.e = 0;
	/** if escape button pressed **/
	if (ev.key.keysym.sym == SDLK_ESCAPE)
		btnkeys.x = 0;
}

