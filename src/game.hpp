#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "world.hpp"
#include <cmath>
#include <random>
#include <sstream>

using namespace std;

struct World;
struct Window;

struct Body
{
    Body *next = nullptr;
    Body *previous = nullptr;
    int pos;
    BodyType type;
};

struct Snake
{
    int head;
    Direction d;
    Body *queue;
    Body *neck;
    bool manger = 0;
};

struct Game
{
    Mixer *mixer; // moteur audio
    World *world;
    Snake snake;
    int score;
    Statut statut;
    int directions[4];
};
void save_game(Game *game, string pathMap);
void init_game(Game *game, string filename);

void feed(Game *game, Block type, int pos);
void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8], SDL_Texture *BodyTexture[3], int delay);
void move_snake(Window *window, Game *game, int *delay);
void change_statut(Statut *statut);
bool keyboard_eventBegin(Game *game, Window *window, int *counter, bool *select); // regarde les actions du clavier
bool keyboard_event(Game *game, Window *window, string pathMap);
bool keyboard_eventLoad(Game *game, Window *window, int *counter, bool *select);
bool keyboard_eventGameOver(Game *game, Window *window);
bool keyboard_eventBreak(Game *game, Window *window, string pathMap);
void load_game(Game *game, string filename);
void spawn(Game *game, Block type);
bool checkBody(Game *game, int pos);
#endif