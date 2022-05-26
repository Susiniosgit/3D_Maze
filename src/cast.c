#include "../headers/header.h"

player_t player;
float buff[num_rays];
/**
 * ray_cast - function to cast array to the wall
 * @ins: the given sdl2 instance
 *
 * Return: nothing
 **/
void ray_cast(SDL_Instance ins)
{
	/** variables for ray, horizontal & vertical distance **/
	float ray_a, hx, hy, hd = 1000000, shade = 1, px, py, rx, ry;
	float vx, vy, vd = 1000000, disT, ray_x, ray_y;
	int i, vtx = 0, htx = 0;
	SDL_Rect top, map;

	top.x = 0, top.y = 0, top.w = SCREEN_WIDTH, top.h = 400;
	map.x = 0, map.y = 0, map.w = (map_x * (map_s * MAP_SCALE));
	map.h = (map_y * (map_s * MAP_SCALE));
	SDL_SetRenderDrawColor(ins.ren, 30, 144, 255, 0);
	SDL_RenderFillRect(ins.ren, &top);

	SDL_SetRenderDrawColor(ins.ren, 76, 76, 76, 0);
	SDL_RenderFillRect(ins.ren, &map);

	ray_a = player.a - DR * 30, ray_a = FixAng(ray_a);
	for (i = 0; i < num_rays; i++)
	{
		/** find the horizontal line coordinates **/
		horizontal_collision(ray_a, &hd, &hx, &hy, &htx);
		/** find the vertical line coordinates **/
		vertical_collision(ray_a, &vd, &vx, &vy, &vtx);
		/** determine the shortest distance **/
		if (hd < vd)
			ray_x = hx, ray_y = hy, disT = hd, shade = 1, buff[i] = hd;
		else
		{
			ray_x = vx, ray_y = vy, disT = vd, shade = 0.5, buff[i] = vd;
			htx = vtx;
		}
		SDL_SetRenderDrawColor(ins.ren, 155, 0, 0, 0);
		px = player.x * MAP_SCALE, py = player.y * MAP_SCALE;
		rx = ray_x * MAP_SCALE, ry = ray_y * MAP_SCALE;
		SDL_RenderDrawLine(ins.ren, px, py, rx, ry);
		/** draw the wall **/
		draw_scene(ins, i, disT, ray_a, shade, ray_x, ray_y, htx);
		ray_a += DR, ray_a = FixAng(ray_a);
	}
}
/**
 * horizontal_collision - function to check the horizontal collision
 * @ray_a: the ray angle
 * @hd: reference to the horizontal distance
 * @hx: reference to the horizonatal x-coordinate
 * @hy: reference to the horizontal y-coordinate
 * @hmtx: the horizontam map texture value
 *
 * Return: nothing
 **/
void horizontal_collision(float ray_a, float *hd, float *hx, float *hy,
			int *hmtx)
{
	/** variables for ray **/
	float ray_x, ray_y, xo, yo, a_tan;
	int diff, val;

	a_tan = -1 / tan(ray_a), diff = 0;
	/** ray looking up **/
	if (ray_a > PI)
	{
		ray_y = (((int)player.y >> 6) << 6) - 0.0001;
		ray_x = ((player.y - ray_y) * a_tan) + player.x;
		yo = -64, xo = -yo * a_tan;
	}
	/** ray looking down **/
	else if (ray_a < PI && ray_a > 0)
	{
		ray_y = (((int)player.y >> 6) << 6) + 64;
		ray_x = ((player.y - ray_y) * a_tan) + player.x;
		yo = 64, xo = -yo * a_tan;
	}
	/** ray parralel to the horizontal line **/
	else if (ray_a == 0 || ray_a == PI)
		ray_x = player.x, ray_y = player.y, diff = 8;

	/** check until the ray hit the wall **/
	while (diff < 8)
	{
		val = hit_wall(ray_x, ray_y);
		/** if the ray hits the wall, quit the loop **/
		if (val != 0)
		{
			diff = 8;
			if (val > 0)
				*hmtx = val - 1;
		}
		else
			ray_x += xo, ray_y += yo, diff += 1;
	}
	*hx = ray_x, *hy = ray_y;
	/** find the distance b/n the player and the ray that hits the wall **/
	*hd = find_distance(player.x, player.y, ray_x, ray_y);
}
/**
 * vertical_collision - function to check vertical collission
 * @ray_a: the angle of the ray
 * @vd: reference to the vertical distance
 * @vx: reference to the vertical x-coordinate
 * @vy: reference to the vertical y-coordinate
 * @vmtx: the vertical map texture value
 *
 * Return: nothing
 **/
void vertical_collision(float ray_a, float *vd, float *vx, float *vy,
			int *vmtx)
{
	/** variables for the vertical collision detection **/
	float ray_x, ray_y, xo, yo, a_tan;
	int diff, val;

	a_tan = -tan(ray_a);
	diff = 0;
	/** the ray parrale to the vertical line **/
	if (ray_a == 0 || ray_a == PI)
		ray_x = player.x, ray_y = player.y, diff = 8;
	/** looking to the left **/
	else if (ray_a > PI2 && ray_a < PI3)
	{
		ray_x = (((int)player.x >> 6) << 6) - 0.0001;
		ray_y = ((player.x - ray_x) * a_tan) + player.y;
		xo = -64, yo = -xo * a_tan;
	}
	/** looking to the right **/
	else if ((ray_a < PI2 || ray_a > PI3) && ray_a)
	{
		ray_x = (((int)player.x >> 6) << 6) + 64;
		ray_y = ((player.x - ray_x) * a_tan) + player.y;
		xo = 64, yo = -xo * a_tan;
	}
	/** check until the ray hits the wall **/
	while (diff < 8)
	{
		val = hit_wall(ray_x, ray_y);
		/** quit the loop if the ray hits the wall **/
		if (val != 0)
		{
			diff = 8;
			if (val > 0)
				*vmtx = val - 1;
		}
		else
			ray_x += xo, ray_y += yo, diff += 1;
	}
	*vx = ray_x, *vy = ray_y;
	/** find the distance b/n the player & the ray hit the vertical line **/
	*vd = find_distance(player.x, player.y, ray_x, ray_y);
}
/**
 * hit_wall - function to check whether the ray hits the wall
 * @rx: the x positon of the ray
 * @ry: the y position of the ray
 * Return: 1 if the ray hists the wall 0 otherwise
 **/
int hit_wall(float rx, float ry)
{
	int mx, my, mp;

	/** if the ray is beyond the boundery **/
	if (rx < 0 || rx >= map_x * map_s || ry < 0 || ry >= map_y * map_s)
		return (-1);
	/** approximate to the nearest int value **/
	mx = floor(rx / map_s);
	my = floor(ry / map_s);
	mp = my * map_x + mx;
	/** if the ray hits the wall **/
	if (mp > 0 && mp < map_x * map_y && getmap_value(mx, my, 0) > 0)
		return (getmap_value(mx, my, 0));
	else
		return (0);
}
/**
 * find_distance - function to find the distance b/n two points
 * @ax: the x-coordinate of the first point
 * @ay: the y-coordinate of the first point
 * @bx: the x-coordinate of the second point
 * @by: the y-coordinate of the second point
 *
 * Return: the distance
 **/
float find_distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
