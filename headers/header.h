#ifndef Demo_h
#define Demo_h

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 600
#define gun_scale 0.35
#define map_x 8
#define map_y 8
#define map_s 64
#define PI 3.14159265
#define PI2 (0.5 * PI)
#define PI3 (1.5 * PI)
#define DR 0.0174533
#define MAP_SCALE 0.25
#define num_enemy 5
#define FOV (PI / 3)
#define RAD_DEG 57.296
#define num_rays 60

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

/**
 * struct SDL_Instance - structure for sdl instance
 * @win: window of sdl
 * @ren: surface to draw
 *
 * Decscription: structure to create window and surface of SDL
**/
typedef struct SDL_Instance
{
	SDL_Window *win;
	SDL_Renderer *ren;
} SDL_Instance;

/**
 * struct btn_keys - structure for event keys
 * @w: up key
 * @a: down key
 * @d: right key
 * @a: left key
 * @e: key for open door
 * @x: key for exit
 * @s: down key
 *
 * Description: structure for handling movement & rotation
 **/
typedef struct btn_keys
{
	int w, a, d, s, e, x;
} btn_keys;

/**
 * struct player_s - struburte for the player
 * @x: the x coordinate postion
 * @y: the y coordinate position
 * @w: the width of the player
 * @h: the height of the player
 * @a: angle of the player
 * @dx: delta x of the player
 * @dy: delta y of the player
 **/
typedef struct player_s
{
	float x, y, w, h, a, dx, dy;
} player_t;

extern player_t player;

/**
 * struct enemy_s - structure for the enemy
 * @x: the x coordinate postion
 * @y: the y coordinate position
 * @z: the z coordinate
 * @path: the given path of the image
 **/
typedef struct enemy_s
{
	float x, y, z;
	char *path;
} enemy_t;

extern enemy_t enemy;
extern float buff[num_rays];

/** main.c **/
void init_game(void);
void display(SDL_Instance instance);

/** input **/
int poll_events(SDL_Instance instance);
void handle_key_down(SDL_Instance instance);
void key_up(SDL_Event ev);
void key_down(SDL_Event ev);
void handle_door(void);

/** window **/
int init_instance(SDL_Instance *in);
float FixAng(float a);

/** draw **/
void display_player(SDL_Instance instance);
void draw_map(SDL_Instance ins);
void draw_scene(SDL_Instance ins, int n, float h, float ray_a, float shade,
		float rx, float ry, int m_txr);
void draw_floor(SDL_Instance ins, float ln_off, int n, float line, float ra);
void draw_roof(SDL_Instance ins, float ln_off, int n, float line, float ra);

/** cast **/
void ray_cast(SDL_Instance ins);
int hit_wall(float rx, float ry);
void horizontal_collision(float ray_a, float *d, float *hx, float *hy, int *h);
void vertical_collision(float ray_a, float *vd, float *vx, float *vy, int *v);
float find_distance(float ax, float ay, float bx, float by);

/** draw2 **/
void add_weapon(SDL_Instance ins);
void add_enemy(SDL_Instance ins);
float find_viewdistance(void);
void draw_sprite_map(SDL_Instance ins);
void sort_sprite(int *sprite, double *spr_dis, int n);

/** texture **/
float get_texture(int idx);

/** map **/
void setmap_value(int mx, int my, int val);
int getmap_value(int x, int y, int mp);
void free_numbers(int **numbers);
void make_map(char **argv);

/** get_map **/
int _atoi(char *s);
char *_strdup(char *str);
int _length(char *str);
int **get_altitude(char **argv);
char **str_split(char *str, char *del);

/** free_mem **/
void free_grid(SDL_Point ***grid);
void free_tokens(char **tokens);
void free_cols(char ***cols);
void free_numbers(int **numbers);
#endif
