#include "../headers/header.h"

enemy_t enemies[num_enemy] = {
	{79.4, 84.4, 0, "images/enm.png"},
	{250.5, 100, 5, "images/enm222.png"},
	{390.5, 205, 5, "images/enm33.png"},
	{430, 384, 5, "images/enm.png"},
	{80.3, 445.7, 5, "images/enm111.png"}
};

/**
 * add_weapon - function to draw a weapon
 * @ins: the given instance
 *
 * Return: nothing
 **/
void add_weapon(SDL_Instance ins)
{
	/** variables for the sdl, width & height **/
	SDL_Texture *texture = NULL;
	SDL_Rect gun;
	int w, h;
	SDL_Surface *surf = IMG_Load("images/gn111.png");

	/** if the image found **/
	if (surf)
	{
		/** remove the background white color **/
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 255, 255));
		/** create a texture **/
		texture = SDL_CreateTextureFromSurface(ins.ren, surf);
		/** query the texture to find width & height of the image **/
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		gun.w = w * gun_scale, gun.h =  h * gun_scale;
		gun.x = (SCREEN_WIDTH - gun.w) / 2;
		gun.y = (SCREEN_HEIGHT - gun.h) + 20;

		/** draw the weapon with the above specification **/
		if (texture)
			SDL_RenderCopy(ins.ren, texture, NULL, &gun);
		else
			printf("unable to create texture\n");
		/** free & destroy the surface **/
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(texture);
	}
	else
		printf("unable to crate a surface\n");
}
/**
 * add_enemy - function to draw an enemy
 * @ins: the given instance
 *
 * Return: nothing
 **/
void add_enemy(SDL_Instance ins)
{
	SDL_Texture *texture = NULL;
	SDL_Rect en;
	int w, h, i;
	float dx, dy, ds, sx, DPP, e_a, e_d, e_swidth, ex;

	/** for each enemy **/
	for (i = 0; i < num_enemy; i++)
	{
		/** load the image **/
		SDL_Surface *surf = IMG_Load(enemies[i].path);

		/** if image found **/
		if (surf)
		{
			/** remove the background color & create a texture **/
			SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format,
					255, 255, 255));
			texture = SDL_CreateTextureFromSurface(ins.ren, surf);
			SDL_QueryTexture(texture, NULL, NULL, &w, &h);
			/** disance b/n player & sprite **/
			dx = enemies[i].x - player.x, dy = enemies[i].y - player.y;
			ds = sqrt(dx * dx + dy * dy);
			/** angele & dis of the enemy relative to the player **/
			e_a = atan2(dy, dx) - player.a, e_d = cos(e_a) * ds;
			/** find distance to the projection plane **/
			DPP = find_viewdistance(), e_swidth = map_s * DPP / e_d;
			sx = tan(e_a) * DPP;
			/** find the screen postion of the sprite **/
			en.x = (SCREEN_WIDTH / 2) + sx - (e_swidth / 2);
			ex = e_d / 4, en.y = (SCREEN_HEIGHT - e_swidth) / 2.0f;
			en.w = e_swidth, en.h = e_swidth;
			/** if the sprite is not far from the player **/
			if (texture && ex > 0 && ex < num_rays &&
				en.y < buff[(int)ex])
				SDL_RenderCopy(ins.ren, texture, NULL, &en);
		}
		/** free & destroy the surface **/
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(texture);
	}
}
/**
 * find_viewdistance - fucntion to find the view point distance
 *
 * Return: the view point distance
 **/
float find_viewdistance(void)
{
	/** variable for the screen width, feild of view **/
	float swdth = SCREEN_WIDTH / 2, a = FOV / 2;

	return (swdth / tan(a));
}
/**
 * draw_sprite_map - function to draw sprite map
 * @ins: the given instance
 *
 * Return: nothign
 **/
void draw_sprite_map(SDL_Instance ins)
{
	/** variable for the sprite coordinate **/
	SDL_Rect rct;
	float sp_x, sp_y;
	int i;

	/** for each sprite **/
	for (i = 0; i < num_enemy; i++)
	{
		/** minimize the sprite postion relative to the map **/
		sp_x = enemies[i].x * MAP_SCALE;
		sp_y = enemies[i].y * MAP_SCALE;
		rct.x = sp_x - 2, rct.y = sp_y - 2;
		rct.w = 5, rct.h = 5;
		/** draw the map of the sprite **/
		SDL_SetRenderDrawColor(ins.ren, 0, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(ins.ren, &rct);
	}
}

/**
 * sort_sprite - fucntion to sort the sprite
 * @sprite: the given sprite
 * @spr_dis: the distance of each sprite
 * @n: the  number of sprite
 *
 * Return: nothing
 **/
void sort_sprite(int *sprite, double *spr_dis, int n)
{
	/** temporary variable for bubble sort **/
	int i, j, t;
	double tmp;

	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			/** if the previous distance is less than the next **/
			if (spr_dis[i] < spr_dis[j])
			{
				tmp = spr_dis[i];
				t = spr_dis[i];
				spr_dis[i] = spr_dis[j];
				sprite[i] = sprite[j];
				spr_dis[j] = tmp;
				sprite[j] = t;
			}
		}
	}
}

