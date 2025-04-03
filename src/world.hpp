#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
using namespace std;

enum Block;

struct World
{
    int width;
    int height;
    Block *grid;
};

void init_world(World *world, int w, int h);
void free_world(World *world);
void write(World *world, int x, int y, Block b);
void display(World *world);
void init_world_from_file(World *word, string filename);
int getId(int x, int y, int w);
#endif