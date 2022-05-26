#include "../headers/header.h"

int map[map_y][map_x] = {
	{1, 1, 1, 1, 1, 3, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 4, 1, 0, 0, 0, 1},
	{2, 0, 0, 0, 0, 0, 0, 3},
	{2, 0, 0, 0, 1, 0, 0, 1},
	{2, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 2, 1, 1, 1, 1},
	};

int map_floor[map_y][map_x] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 2, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	};


/**
 * getmap_value - find the value of the map at agiven coordinate
 * @x: x-coordinate
 * @y: y-coordinate
 * @mp: the required map type
 *
 * Return: the value at x,y
 **/
int getmap_value(int x, int y, int mp)
{
	/** if the map floor is required **/
	if (mp == 1)
		return (map_floor[y][x]);
	else
		return (map[y][x]);
}

/**
 * setmap_value - set the value of map at a given coordinate
 * @x: x-coordinate
 * @y: y-coordinate
 * @val: the value to set
 *
 * Return: nothing
 **/
void setmap_value(int x, int y, int val)
{
	/** set the map value to argument val **/
	map[y][x] = val;
}
/**
 * make_map - function to make map from the given file
 * @argv: the array of the given argument
 *
 * Return: nothing
 **/
void make_map(char **argv)
{
	int i, j;
	int **file_map;

	/** get the map value form the file **/
	file_map = get_altitude(argv);
	/** update the map value with value parsed from the file **/
	for (i = 0; i < map_x; i++)
	{
		for (j = 0; j < map_y; j++)
			map[i][j] = file_map[i][j];
	}
	/** free the allocated map **/
	free_numbers(file_map);
}
