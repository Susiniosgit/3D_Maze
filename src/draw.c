#include "../headers/header.h"

player_t player;
/**
 * display_player - function to display the player
 * @instance: the given sdl2 instance
 *
 * Return: nothing
 **/
void display_player(SDL_Instance instance)
{
	/** variables for the intial & finall coordiantes & for SDL_rect **/
	SDL_Rect rect;
	float x0, y0, x1, y1;

	/** convert the player postion into map scale **/
	rect.x = player.x * MAP_SCALE, rect.y = player.y * MAP_SCALE;
	rect.w = player.w * MAP_SCALE, rect.h = player.w * MAP_SCALE;
	/** draw the rectangle of the player **/
	SDL_SetRenderDrawColor(instance.ren, 255, 255, 0, 0);
	SDL_RenderFillRect(instance.ren, &rect);

	/** draw the line sight of the player **/
	x0 = player.x * MAP_SCALE;
	y0 = player.y * MAP_SCALE;
	x1 = (player.x + player.dx * 20) * MAP_SCALE;
	y1 = (player.y + player.dy * 20) * MAP_SCALE;
	SDL_RenderDrawLine(instance.ren, x0, y0, x1, y1);
}

/**
 * draw_map - function to draw a map
 * @ins: the given SDL instance
 *
 * Return: nothing
 **/
void draw_map(SDL_Instance ins)
{
	/** variable for x & y coordinate of the map **/
	int x, y;
	SDL_Rect rect;

	for (x = 0; x < map_x; x++)
	{
		for (y = 0; y < map_y; y++)
		{
			/** set the wall color to white & empty to black **/
			if (getmap_value(y, x, 0) > 0)
				SDL_SetRenderDrawColor(ins.ren, 255, 255, 255, 0);
			else
				SDL_SetRenderDrawColor(ins.ren, 0, 0, 0, 0);
			/** draw the minmized map **/
			rect.x = (y * map_s * MAP_SCALE) + 1;
			rect.y = (x * map_s * MAP_SCALE) + 1;
			rect.w = (map_s * MAP_SCALE) - 1;
			rect.h = (map_s * MAP_SCALE) - 1;
			SDL_RenderFillRect(ins.ren, &rect);
		}
	}
}

/**
 * draw_scene - function to draw the scene
 * @ins: the given instance
 * @n: the ray number
 * @h: the height
 * @ray_a: the angle of the ray
 * @shd: the shading value
 * @rx: the x coordinate of the ray
 * @ry: the y coordinate of the ray
 * @m_txr: the map texture value
 *
 * Return: nothing
 **/
void draw_scene(SDL_Instance ins, int n, float h, float ray_a, float shd,
		float rx, float ry, int m_txr)
{
	/** variables for wall drawing **/
	float line, a = FixAng(player.a - ray_a), of, tx_y = 0, tx_x, tx_s, c;
	int j, i, idx, s = (int) SCREEN_WIDTH / 60;

	h = h * cos(a), line = (map_s * 420) / h, tx_s = 32.0 / (float)line;
	/** line offset * line limit **/
	of = 280 - (line / 2);
	if (line > 420)
		line = 420, tx_y = (line - 420) / 2.0;
	tx_y = (tx_y * tx_s) + (m_txr * 32);
	/** shade the wall if it is 1 **/
	if (shd == 1)
	{
		tx_x = (int) (rx / 2.0) % 32;
		if (ray_a > PI)
			tx_x = 31 - tx_x;
	}
	else
	{
		tx_x = (int) (ry / 2.0) % 32;
		if (ray_a > PI2 && ray_a < PI3)
			tx_x = 31 - tx_x;
	}
	/** draw the wall with the above specification **/
	for (i = 0; i < line; i++)
	{
		idx = (int)(tx_y) * 32 + (int)tx_x, c = (get_texture(idx) * 255) * shd;
		if (m_txr == 0)
			SDL_SetRenderDrawColor(ins.ren, c, c / 2.0, c / 2.0, 0);
		if (m_txr == 1)
			SDL_SetRenderDrawColor(ins.ren, c, c, c / 2.0, 0);
		if (m_txr == 2)
			SDL_SetRenderDrawColor(ins.ren, c / 2.0, c / 2.0, c, 0);
		if (m_txr == 3)
			SDL_SetRenderDrawColor(ins.ren, c / 2.0, c, c / 2.0, 0);
		for (j = n * s; j < (n * s) + s; j++)
			SDL_RenderDrawPoint(ins.ren, j, i + of);
		tx_y += tx_s;
	}
	draw_floor(ins, of, n, line, ray_a); /** draw the ceiling **/
}
/**
 * draw_floor - function to draw a floor)
 * @ln_off: the line offset
 * @line: the vertical line
 * @ra: the ray angle
 * @n: the index of each ray
 * @ins: the given instance
 *
 * Return: nothing
 **/
void draw_floor(SDL_Instance ins, float ln_off, int n, float line, float ra)
{
	/** variable for the floor **/
	int i, j, idx, s = (int) SCREEN_WIDTH / 60;
	float dy, fix, tx_x, tx_y, clr, pa = player.a;

	/** start from where the wall stops & draw the floor **/
	for (i = ln_off + line; i < SCREEN_HEIGHT; i++)
	{
		dy = i - (520 / 2.0), fix = cos(FixAng(pa - ra));
		tx_x = player.x / 2.0 + cos(ra) * 158 * 32 / dy / fix;
		tx_y = player.y / 2.0 - sin(ra) * 158 * 32 / dy / fix;
		/**
		*mp = (int)(tx_y / 32.0);
		*mp = getmap_value((int)(tx_x / 32.0), mp, 1) * 32 * 32;
		*idx = ((int)(tx_y)&31) * 32 + ((int)(tx_x) & 31) + mp;
		**/
		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		clr = (get_texture(idx) * 255) * 0.7;
		SDL_SetRenderDrawColor(ins.ren, clr / 1.3, clr / 1.3, clr, 0);
		for (j = n * s; j < (n * s) + s; j++)
			SDL_RenderDrawPoint(ins.ren, j, i);
	}
}

/**
 * draw_roof - function to draw a roof)
 * @ln_off: the line offset
 * @line: the vertical line
 * @ra: the ray angle
 * @ins: the given instance
 * @n: the index of each ray
 *
 * Return: nothing
 **/
void draw_roof(SDL_Instance ins, float ln_off, int n, float line, float ra)
{
	/** variables for the ceiling **/
	int i, j, idx;
	float dy, fix, tx_x, tx_y, c, pa = player.a;

	/** starts from the begenning upt to the wall & draw the ceiling **/
	for (i = ln_off + line; i < 500; i++)
	{
		dy = i - (500 / 2.0), fix = cos(FixAng(pa - ra));
		tx_x = player.x / 2.0 + cos(ra) * 158 * 32 / dy / fix;
		tx_y = player.y / 2.0 - sin(ra) * 158 * 32 / dy / fix;
		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		c = (get_texture(idx) * 255) * 0.7;
		SDL_SetRenderDrawColor(ins.ren, c / 2.0, c / 1.2, c / 2.0, 0);
		for (j = n * 8; j < (n * 8) + 8; j++)
			SDL_RenderDrawPoint(ins.ren, j + 530, 500 - i);
	}
}
