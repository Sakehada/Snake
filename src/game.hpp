#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
using namespace std;

struct World;
struct Window;

int* directions;

struct Statut{
    Begin,
    Play,
    Pause,
    End
};

struct Body{
    Body* next;
    Body* previous;
    int* pos;
    BodyType type;
}

struct Snake{
    int head;
    Direction* d;
    Body* queue;
    Body* neck;
}

struct Game
{
    World *world;
    Snake snake;
};

void init_game(Game *game, string filename);
void display_game(Window *window, Game *game);
void move_ball(Window *window, Game *game);
void change_statut(Statut *statut);
bool keyboard_event(Game *game, Window* window, string pathMap);
#endif