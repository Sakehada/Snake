#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "world.hpp"
#include <cmath>
#include <random>

using namespace std;

struct World;
struct Window;

struct Body
{
    Body *next;
    Body *previous;
    int pos;
    BodyType type;
};

struct Snake
{
    int head;
    Direction d;
    Body *queue;
    Body *neck;
    bool manger;
};

struct Game
{
    World *world;
    Snake snake;
    int score;
    Statut statut;
    
};

void init_game(Game *game, string filename);
void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8], SDL_Texture *TextureBody[3]);
void move_snake(Window *window, Game *game);
void change_statut(Statut *statut);
bool keyboard_event(Game *game, Window *window, string pathMap);
#endif