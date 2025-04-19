#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "world.hpp"

using namespace std;

struct World;
struct Window;
/*
struct Body
{
    Body *next;
    Body *previous;
    int *pos;
    BodyType type;
};

struct Snake
{
    int head;
    Direction *d;
    Body *queue;
    Body *neck;
};
*/
struct Game
{
    World *world;
    // Snake snake;
    int score;
    Statut statut;
};

void init_game(Game *game, string filename);
void display_game(Window *window, Game *game, SDL_Texture *FoodRed, SDL_Texture *FoodBlue, SDL_Texture *FoodGreen, SDL_Texture *FoodStar, SDL_Texture *BackgroundTux);
// void move_ball(Window *window, Game *game);
void change_statut(Statut *statut);
bool keyboard_event(Game *game, Window *window, string pathMap);
#endif