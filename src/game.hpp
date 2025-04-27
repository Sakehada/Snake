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
<<<<<<< HEAD
    Body *next;
    Body *previous;
=======
    Body *next = nullptr;
    Body *previous = nullptr;
>>>>>>> origin/anis
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
    int directions[4];
};

void init_game(Game *game, string filename);
<<<<<<< HEAD
void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8], SDL_Texture *TextureBody[3]);
void move_snake(Window *window, Game *game);
=======
void feed(Game *game, BodyType type, int pos);
void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8], SDL_Texture *BodyTexture[3], int delay);
void move_snake(Window *window, Game *game, int* delay);
>>>>>>> origin/anis
void change_statut(Statut *statut);
bool keyboard_event(Game *game, Window *window, string pathMap);
#endif